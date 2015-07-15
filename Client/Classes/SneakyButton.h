//
//  SneakyButton.h
//  TestApp
//
//  Created by Mengjiangtao on 7/7/15.
//
//

#ifndef __TestApp__SneakyButton__
#define __TestApp__SneakyButton__

#include "cocos2d.h"
USING_NS_CC;

class SneakyButton:public cocos2d::Node
{
protected:
    Point center;
    float radiusSq;
    Rect bounds;
    
    CC_SYNTHESIZE(bool, status, Status);
    CC_SYNTHESIZE_READONLY(bool, active, IsActive);
    CC_SYNTHESIZE_READONLY(bool, value, Value);
    CC_SYNTHESIZE(bool, isHoldable, IsHoldable);
    CC_SYNTHESIZE(bool, isToggleable, IsToggleable);
    CC_SYNTHESIZE(float, rateLimit, RateLimit);
    
    CC_SYNTHESIZE_READONLY(float, radius, Radius);
    
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    bool initWithRect(Rect rect);
    void limiter(float delta);
    void setRadius(float r);
//    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event);
//    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event);
//    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event);
//    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event);
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    virtual void onTouchCancelled(Touch *touch, Event *event);
};

#endif /* defined(__TestApp__SneakyButton__) */
