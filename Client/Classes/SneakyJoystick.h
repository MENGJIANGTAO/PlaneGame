//
//  SneakyJoystick.h
//  TestApp
//
//  Created by Mengjiangtao on 7/8/15.
//
//

#ifndef __TestApp__SneakyJoystick__
#define __TestApp__SneakyJoystick__

#include "cocos2d.h"
USING_NS_CC;

class SneakyJoystick : public cocos2d::Node
{
protected:
    float joystickRadiusSq;
    float thumbRadiusSq;
    float deadRadiusSq;
    
    CC_SYNTHESIZE_READONLY(Point, stickPosition, StickPosition);
    CC_SYNTHESIZE_READONLY(float, degrees, Degrees);
    CC_SYNTHESIZE_READONLY(Point, velocity, Velocity);
    CC_SYNTHESIZE(bool, autoCenter, AutoCenter);
    CC_SYNTHESIZE_READONLY(bool, isDPad, IsDPad);
    CC_SYNTHESIZE(bool, hasDeadzone, HasDeadzone);
    CC_SYNTHESIZE(int, numberOfDirections, NumberOfDirections);
    
    CC_SYNTHESIZE_READONLY(float, joystickRadius, JoystickRadius);
    CC_SYNTHESIZE_READONLY(float, thumbRadius, ThumbRadius);
    CC_SYNTHESIZE_READONLY(float, deadRadius, DeadRadius);
    
    virtual ~SneakyJoystick();
    
    bool initWithRect(Rect rect);
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    void setIsDPad(bool b);
    void setJoystickRadius(float r);
    void setThumbRadius(float r);
    void setDeadRadius(float r);
//    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event);
//    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event);
//    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event);
//    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event);
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    virtual void onTouchCancelled(Touch *touch, Event *event);
    
//
//    void touchDelegateRelease();
//    void touchDelegateRetain();
    
private:
    void updateVelocity(Point point);
    void setTouchRadius();
    
};

#endif /* defined(__TestApp__SneakyJoystick__) */
