//
//  World.cpp
//  TestApp
//
//  Created by Mengjiangtao on 7/8/15.
//
//

#include "World.h"
#include "Button.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

static World *sh;
bool touchType = true;

World *World::shareWorld()
{
    if(sh)
    {
        return sh;
    }
    return nullptr;
}

Scene* World::createScene()
{
    Scene *scene = Scene::create();
    World *layer = World::create();
    scene->addChild(layer);
    return scene;
}

bool World::init()
{
    if(!Layer::init()){
        return false;
    }
    sh = this;
    SpriteFrameCache *cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("button.plist", "button.png");
    
//    SimpleAudioEngine::getInstance()->playBackgroundMusic("gameMusic.mp3",true);
    
    Player* player = Player::createPlayer("hero.png");
    addChild(player,1,tag_player);
    
    Button *button = Button::createButton(player, this);
    addChild(button);
    
    bulletBatchNode = SpriteBatchNode::create("heroBullet.png");
    this->addChild(bulletBatchNode);
    
    this->schedule(schedule_selector(World::autoCreateEnemy));
    this->schedule(schedule_selector(World::autoCreateBullet),0.5);
    return true;
}


void World::onEnter()
{
    Layer::onEnter();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(World::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void World::onTouchesMoved(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event)
{
    
}


void World::autoCreateEnemy(float dt){
    
    smallEnemyTime++;
    mediumEnemyTime++;
    bigEnemyTime++;
    smallEnemyTime2++;
    mediumEnemyTime2++;
    if(smallEnemyTime > 80)
    {
        Enemy* enemy = NULL;
        enemy = Enemy::createEnemy("enemy_bug.png", 0,0);
        enemys.pushBack(enemy);
        addChild(enemy);
        smallEnemyTime = 0;
    }
    if(mediumEnemyTime > 100)
    {
        Enemy* enemy = NULL;
        enemy = Enemy::createEnemy("enemy_duck.png", 1,0);
        enemys.pushBack(enemy);
        addChild(enemy);
        mediumEnemyTime = 0;
    }
    if(bigEnemyTime > 500)
    {
        Enemy* enemy = NULL;
        enemy = Enemy::createEnemy("enemy_pig.png", 2,0);
        enemys.pushBack(enemy);
        addChild(enemy);
        bigEnemyTime = 0;
    }
    if(smallEnemyTime2 >200)
    {
        Enemy* enemy = NULL;
        enemy = Enemy::createEnemy("enemy_bug.png", 0,2);
        enemys.pushBack(enemy);
        addChild(enemy);
        smallEnemyTime2 = 0;
    }
    if(mediumEnemyTime2 >300)
    {
        Enemy* enemy = NULL;
        enemy = Enemy::createEnemy("enemy_duck.png", 0,1);
        enemys.pushBack(enemy);
        addChild(enemy);
        mediumEnemyTime2 = 0;
    }
}

void World::autoCreateBullet(float dt){
    
    if(this->getVectorForEnemy().size()!=0){
        Player *player = (Player*)this->getChildByTag(tag_player);
        bulletBatchNode->addChild(Bullet::createBullet("heroBullet.png",3.5,player->getPosition()+Vec2(0,player->getContentSize().height*0.5)));
        SimpleAudioEngine::getInstance()->playEffect("effect_bullet.mp3");
    }
}

Vector<Enemy*> World::getVectorForEnemy(){
    return enemys;
}

World::~World()
{
    
}

Player* World::getPlayer(){

    Player* player = (Player*)World::shareWorld()->getChildByTag(tag_player);
    return player;
}