//
//  mainScene.cpp
//  TestApp
//
//  Created by Mengjiangtao on 7/7/15.
//
//

#include "mainScene.h"
#include "World.h"


Scene* mainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = mainScene::create();
    scene->addChild(layer);
    return scene;
}

bool mainScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size size = Director::getInstance()->getWinSize();
    
    MenuItemImage * itemPlay= MenuItemImage::create("play_nor.png", "play_pre.png",this,menu_selector(mainScene::playIsPressed));
    
    Menu* menu = Menu::create(itemPlay,NULL);
    menu->setPosition(Vec2(size.width/2,size.height/3));
    addChild(menu);
    menu->alignItemsHorizontallyWithPadding(10);
    
    return true;
}

void mainScene::playIsPressed(Ref* ref){
    connectionServer();
    Director::getInstance()->replaceScene(CCTransitionFade::create(1, World::createScene()));
}

void mainScene::connectionServer(){
    pthread_t tid;
    socket.Init();
    socket.Create(AF_INET, SOCK_STREAM,0);
    const char *ip = "127.0.0.1";
    int port = 9124;
    bool result = socket.Connect(ip, port);
    socket.Send("getTime", 50);
    if(result){
        CCLOG("connect to server success!");
//        std::thread recvThread = std::thread(&mainScene::receiveData);
//        recvThread.detach();
        if(!pthread_create(&tid, nullptr, receiveData, 0)){
            pthread_join(tid, nullptr);
        }
    }else{
        CCLOG("can not connect to server.");
        return;
    }
}

void *mainScene::receiveData(void *r){
    ODSocket socket;
    socket.Init();
    socket.Create(AF_INET, SOCK_STREAM,0);
    socket.Connect("127.0.0.1", 9124);
    char recvBuf[1024] = "";
    socket.Send("getTime", 1024,1);
    socket.Recv(recvBuf, 1024,0);
    socket.Close();
    socket.Clean();
    return NULL;
}

