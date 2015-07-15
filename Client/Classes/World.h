//
//  World.h
//  TestApp
//
//  Created by Mengjiangtao on 7/8/15.
//
//

#ifndef __TestApp__World__
#define __TestApp__World__

#include "Player.h"
#include "Enemy.h"
#include "SneakyButton.h"
#include "SneakyJoystick.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystickSkinnedBase.h"


class World:public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    static World* shareWorld();
    Player *getPlayer();
    
    
    
    virtual bool init();
    virtual ~World();
    virtual void onEnter();
//    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event);
    
    void autoCreateEnemy(float dt);
    void autoCreateBullet(float dt);
    Vector<Enemy*> getVectorForEnemy();
    
    CREATE_FUNC(World);
    
    SneakyButton *fireButton;
    SneakyJoystick *joystick;
    Vector<Enemy*> enemys;
    
    
    
    SpriteBatchNode *bulletBatchNode;
    float totalTime;
    float nextShotTime;
    
    int smallEnemyTime;
    int mediumEnemyTime;
    int bigEnemyTime;
    int smallEnemyTime2;
    int mediumEnemyTime2;
    
    bool isGetNewRecord;
    
};
#endif /* defined(__TestApp__World__) */
