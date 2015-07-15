//
//  Button.cpp
//  TestApp
//
//  Created by Mengjiangtao on 7/8/15.
//
//

#include "Button.h"

Button* Button::createButton(Player* player, World* world)
{
    Button* button = new Button();
    if(button && button->create())
    {
        button->autorelease();
        button->buttonInit(player, world);
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
}

void Button::buttonInit(Player* player, World* world)
{
    myPlayer = player;
    myWorld = world;
//    SpriteFrameCache * cache = SpriteFrameCache::getInstance();
//    cache->addSpriteFramesWithFile("button.plist","button.png");
    this->addJoystick();
    this->addFireButton();
    this->scheduleUpdate();
}

void Button::update(float time)
{
    totalTime += time;
    if (fireButton->getIsActive() && totalTime > nextShotTime)
    {
        nextShotTime = totalTime + 0.2f;
        //        myWorld->autoCreateBullet(0);
    }
    // Allow faster shooting by quickly tapping the fire button.
    if (!fireButton->getIsActive())
    {
        totalTime = 0;
        nextShotTime = 0;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    Point velocity = joystick->getVelocity()* (10000 * time);
    if(velocity.x != 0 && velocity.y != 0)
    {
        myPlayer->setPosition(Vec2(myPlayer->getPosition().x + velocity.x * time, myPlayer->getPosition().y + velocity.y * time));
        float x = myPlayer->getPositionX();
        float y = myPlayer->getPositionY();
        Size playSize = myPlayer->getContentSize();
        float xMax = winSize.width - playSize.width * 0.5f;
        float yMax = winSize.height - playSize.height * 0.5f;
        if(x > xMax)
        {
            myPlayer->setPositionX(xMax);
        }else if (x < playSize.width * 0.5f)
        {
            myPlayer->setPositionX(playSize.width * 0.5f);
        }
        if(y > yMax)
        {
            myPlayer->setPositionY(yMax);
        }else if(y < playSize.height * 0.5f)
        {
            myPlayer->setPositionY(playSize.height * 0.5f);
        }
    }
    
}

void Button::addJoystick()
{
    float stickRadius = 50;
    joystick = new SneakyJoystick();
    joystick->initWithRect(Rect(0, 0, stickRadius, stickRadius));
    joystick->autorelease();
    joystick->setAutoCenter(true);
    joystick->setIsDPad(true);
    joystick->setNumberOfDirections(360);

    SneakyJoystickSkinnedBase *skinStick = SneakyJoystickSkinnedBase::create();
    skinStick->setPosition(Vec2(stickRadius * 1.5f, stickRadius * 1.5f));
    
    skinStick->setBackgroundSprite(Sprite::createWithSpriteFrameName("control_bg.png"));
    skinStick->setThumbSprite(Sprite::createWithSpriteFrameName("cen.png"));
    
    skinStick->setJoystick(joystick);
    this->addChild(skinStick);
}

void Button::addFireButton()
{
    float buttonRadius = 50;
    Size screenSize = Director::getInstance()->getWinSize();
    fireButton = new SneakyButton();
    fireButton->initWithRect(Rect(0, 0, buttonRadius, buttonRadius));
    fireButton->setIsHoldable(true);
    SneakyButtonSkinnedBase * skinFireButton = SneakyButtonSkinnedBase::create();
    skinFireButton->setPosition(Vec2(screenSize.width - buttonRadius * 1.5f, buttonRadius * 1.5f));
    
    skinFireButton->setDefaultSprite(Sprite::createWithSpriteFrameName("fire_button_default.png"));
    skinFireButton->setPressSprite(Sprite::createWithSpriteFrameName("fire_button_press.png"));
    skinFireButton->setActivatedSprite(Sprite::create("Icon.png"));
    skinFireButton->setDisabledSprite(Sprite::createWithSpriteFrameName("fire_button_default.png"));
    
    skinFireButton->setButton(fireButton);
    this->addChild(skinFireButton);
}