//
//  SneakyButtonSkinnedBase.h
//  TestApp
//
//  Created by Mengjiangtao on 7/7/15.
//
//

#ifndef __TestApp__SneakyButtonSkinnedBase__
#define __TestApp__SneakyButtonSkinnedBase__

#include "SneakyButton.h"

class SneakyButtonSkinnedBase:public Layer
{
    CC_SYNTHESIZE_READONLY(Sprite *, defaultSprite, DefaultSprite);
    CC_SYNTHESIZE_READONLY(Sprite *, activatedSprite, ActivatedSprite);
    CC_SYNTHESIZE_READONLY(Sprite *, disabledSprite, DisabledSprite);
    CC_SYNTHESIZE_READONLY(Sprite *, pressSprite, PressSprite);
    
    CC_SYNTHESIZE_READONLY(SneakyButton *, button, Button); //Not sure about this
    
    //Public methods
    CREATE_FUNC(SneakyButtonSkinnedBase);
    virtual ~SneakyButtonSkinnedBase();
    bool init();
    void watchSelf(float delta);
    void setContentSize(Size s);
    void setDefaultSprite(Sprite *aSprite);
    void setActivatedSprite(Sprite *aSprite);
    void setDisabledSprite(Sprite *aSprite);
    void setPressSprite(Sprite *aSprite);
    void setButton(SneakyButton *aButton);
};

#endif /* defined(__TestApp__SneakyButtonSkinnedBase__) */
