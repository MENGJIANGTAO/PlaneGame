//
//  SneakyButton.cpp
//  TestApp
//
//  Created by Mengjiangtao on 7/7/15.
//
//

#include "SneakyButton.h"

void SneakyButton::onEnterTransitionDidFinish()
{}

void SneakyButton::onExit()
{}

bool SneakyButton::initWithRect(cocos2d::Rect rect)
{
    bool pRet = false;
    bounds = Rect(0,0,rect.size.width,rect.size.height);
    center = Point(rect.size.width/2, rect.size.height/2);
    status = 1;
    active = false;
    value = 0;
    isHoldable = 0;
    isToggleable = 0;
    radius = 32.0f;
    rateLimit = 1.0f/120.0f;
    setPosition(rect.origin);
    pRet = true;
    return true;
}

void SneakyButton::limiter(float delta)
{
    value = 0;
    this->unschedule(schedule_selector(SneakyButton::limiter));
    active = false;
}

void SneakyButton::setRadius(float r)
{
    radius = r;
    radiusSq = r*r;
}

void SneakyButton::onEnter()
{
    Node::onEnter();

//    auto listener = EventListenerTouchAllAtOnce::create();
//    listener->onTouchesBegan = CC_CALLBACK_2(SneakyButton::onTouchesBegan, this);
//    listener->onTouchesMoved = nullptr;//CC_CALLBACK_2(SneakyButton::onTouchesMoved, this);
//    listener->onTouchesEnded = CC_CALLBACK_2(SneakyButton::onTouchesEnded, this);
//    listener->onTouchesCancelled = CC_CALLBACK_2(SneakyButton::onTouchesCancelled, this);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(SneakyButton::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SneakyButton::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SneakyButton::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//void SneakyButton::onTouchesBegan(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event)
bool SneakyButton::onTouchBegan(Touch *touch, Event *event)
{
    if(active) return false;
//    Vector<Touch*>::const_iterator touchIter = touch.begin();
//    while(touchIter != touch.end())
//    {
//        Touch *pTouch = (Touch*)(*touchIter);
        Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
        location = this->convertToNodeSpace(location);
        if(location.x < - radius || location.x > radius || location.y < -radius || location.y > radius)
            return false;
        else{
            float dSq = location.x*location.x + location.y*location.y;
            if(radiusSq > dSq){
                active = true;
                if (!isHoldable && !isToggleable){
                    value = 1;
                    this->schedule(schedule_selector(SneakyButton::limiter), rateLimit);
                }
                if (isHoldable) value = 1;
                if (isToggleable) value = !value;
            }
        }
//        ++ touchIter;
//    }
        return true;
}

//void SneakyButton::onTouchesMoved(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event)
void SneakyButton::onTouchMoved(Touch *touch, Event *event)
{
    if (!active) return;
//    Vector<Touch*>::const_iterator touchIter = touch.begin();
//    while(touchIter != touch.end())
//    {
//        Touch *pTouch = (Touch*)(*touchIter);
        Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
        location = this->convertToNodeSpace(location);
        //Do a fast rect check before doing a circle hit check:
        if(location.x < -radius || location.x > radius || location.y < -radius || location.y > radius){
            return;
        }else{
            float dSq = location.x*location.x + location.y*location.y;
            if(radiusSq > dSq){
                if (isHoldable) value = 1;
            }
            else {
                if (isHoldable) value = 0; active = false;
            }
        }
//        ++ touchIter;
//    }
}

//void SneakyButton::onTouchesEnded(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event)
void SneakyButton::onTouchEnded(Touch *touch, Event *event)
{
    if (!active) return;
    if (isHoldable) value = 0;
    if (isHoldable||isToggleable) active = false;
}

//void SneakyButton::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event)
void SneakyButton::onTouchCancelled(Touch *touch, Event *event)
{
//    onTouchesEnded(touch,event);
    onTouchEnded(touch,event);
}