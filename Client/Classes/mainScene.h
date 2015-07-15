//
//  mainScene.h
//  TestApp
//
//  Created by Mengjiangtao on 7/7/15.
//
//

#ifndef __TestApp__mainScene__
#define __TestApp__mainScene__

#include "cocos2d.h"
#include "ODSocket.h"

USING_NS_CC;

class mainScene:public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    void playIsPressed(Ref* ref);
    static void *receiveData(void *r);
    void connectionServer();
    CREATE_FUNC(mainScene);
private:
    ODSocket socket;
    
};

#endif /* defined(__TestApp__mainScene__) */
