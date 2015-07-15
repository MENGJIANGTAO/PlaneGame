//
//  SneakyJoystickSkinnedBase.h
//  TestApp
//
//  Created by Mengjiangtao on 7/8/15.
//
//

#ifndef __TestApp__SneakyJoystickSkinnedBase__
#define __TestApp__SneakyJoystickSkinnedBase__

#include "cocos2d.h"
#include "SneakyJoystick.h"
USING_NS_CC;

class SneakyJoystickSkinnedBase : public cocos2d::Layer
{
public:
    CC_SYNTHESIZE_READONLY(Sprite *, backgroundSprite, BackgroundSprite);
    CC_SYNTHESIZE_READONLY(Sprite *, thumbSprite, ThumbSprite);
    CC_SYNTHESIZE_READONLY(SneakyJoystick *, joystick, Joystick);
    
    //Public methods
    CREATE_FUNC(SneakyJoystickSkinnedBase);
    virtual ~SneakyJoystickSkinnedBase();
    bool init();
    void updatePositions(float delta);
    virtual void setContentSize(Size s);
    void setBackgroundSprite(Sprite *aSprite);
    void setThumbSprite(Sprite *aSprite);
    void setJoystick(SneakyJoystick *aJoystick);
};

#endif /* defined(__TestApp__SneakyJoystickSkinnedBase__) */
