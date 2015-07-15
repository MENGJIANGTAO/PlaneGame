//
//  Bullet.h
//  TestApp
//
//  Created by Mengjiangtao on 7/9/15.
//
//

#ifndef __TestApp__Bullet__
#define __TestApp__Bullet__

#include "cocos2d.h"
USING_NS_CC;

class Bullet : public cocos2d::Sprite{
  
public:
    static Bullet* createBullet(const char *_filename,float _speed,Point _position);
private:
    void bulletInit(float _speed,Point _position);
    void update(float time);
    virtual void onExit();
    float speed;
};

#endif /* defined(__TestApp__Bullet__) */
