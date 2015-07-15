//
//  Enemy.h
//  TestApp
//
//  Created by Mengjiangtao on 7/9/15.
//
//

#ifndef __TestApp__Enemy__
#define __TestApp__Enemy__

#include "cocos2d.h"
USING_NS_CC;

class Enemy:public cocos2d::Sprite{
public:
    int scoreValue;
    int hp;
    static Enemy* createEnemy(const char* filename,int _type,int _way);
private:
    int way;
    bool isActed;
    void enemyInit(const char* filename,int _type,int _way);
    void createAnimate(const char* fileName,int allCount);
    void update(float time);
    void removeSelf();
};

#endif /* defined(__TestApp__Enemy__) */
