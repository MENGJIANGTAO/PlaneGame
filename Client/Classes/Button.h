//
//  Button.h
//  TestApp
//
//  Created by Mengjiangtao on 7/8/15.
//
//

#ifndef __TestApp__Button__
#define __TestApp__Button__

#include "cocos2d.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "World.h"
USING_NS_CC;

class Button : public cocos2d::Layer
{
public:
    SneakyButton *fireButton;
    SneakyJoystick *joystick;
    Player* myPlayer;
    World* myWorld;
    float totalTime;
    float nextShotTime;
    
public:
    static Button* createButton(Player* player, World* world);
    
private:
    void buttonInit(Player* player, World* world);
//    void buttonInit();
    void update(float time);
    
    void addFireButton();
    void addJoystick();
};

#endif /* defined(__TestApp__Button__) */
