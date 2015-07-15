//
//  SneakyJoystick.cpp
//  TestApp
//
//  Created by Mengjiangtao on 7/8/15.
//
//

#include "SneakyJoystick.h"

#define SJ_PI 3.14159265359f
#define SJ_PI_X_2 6.28318530718f
#define SJ_RAD2DEG 180.0f/SJ_PI
#define SJ_DEG2RAD SJ_PI/180.0f

SneakyJoystick::~SneakyJoystick()
{
}

bool SneakyJoystick::initWithRect(Rect rect)
{
    bool pRet = false;
    //if(CCSprite::init()){
    stickPosition = Vec2(0,0);
    degrees = 0.0f;
    velocity = Vec2(0,0);
    autoCenter = true;
    isDPad = false;
    hasDeadzone = false;
    numberOfDirections = 4;
    
    this->setJoystickRadius(rect.size.width/2);
    this->setThumbRadius(32.0f);
    this->setDeadRadius(0.0f);
    
    //Cocos node stuff
    setPosition(rect.origin);
    pRet = true;
    //}
    return pRet;
}

void SneakyJoystick::onEnterTransitionDidFinish()
{
}

void SneakyJoystick::onExit()
{
}

float round(float r) {
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

void SneakyJoystick::updateVelocity(Point point)
{
    // Calculate distance and angle from the center.
    float dx = point.x;
    float dy = point.y;
    float dSq = dx * dx + dy * dy;
    
    if(dSq <= deadRadiusSq){
        velocity = Vec2(0,0);
        degrees = 0.0f;
        stickPosition = point;
        return;
    }
    
    float angle = atan2f(dy, dx); // in radians
    if(angle < 0){
        angle		+= SJ_PI_X_2;
    }
    float cosAngle;
    float sinAngle;
    
    if(isDPad){
        float anglePerSector = 360.0f / numberOfDirections * SJ_DEG2RAD;
        angle = round(angle/anglePerSector) * anglePerSector;
    }
    
    cosAngle = cosf(angle);
    sinAngle = sinf(angle);
    
    // NOTE: Velocity goes from -1.0 to 1.0.
    if (dSq > joystickRadiusSq || isDPad) {
        dx = cosAngle * joystickRadius;
        dy = sinAngle * joystickRadius;
    }
    
    velocity = Vec2(dx/joystickRadius, dy/joystickRadius);
    degrees = angle * SJ_RAD2DEG;
    
    // Update the thumb's position
    stickPosition = Vec2(dx, dy);
}

void SneakyJoystick::setIsDPad(bool b)
{
    isDPad = b;
    if(isDPad){
        hasDeadzone = true;
        this->setDeadRadius(10.0f);
    }
}

void SneakyJoystick::setJoystickRadius(float r)
{
    joystickRadius = r;
    joystickRadiusSq = r*r;
}

void SneakyJoystick::setThumbRadius(float r)
{
    thumbRadius = r;
    thumbRadiusSq = r*r;
}

void SneakyJoystick::setDeadRadius(float r)
{
    deadRadius = r;
    deadRadiusSq = r*r;
}

void SneakyJoystick::onEnter()
{
    Node::onEnter();
//    auto listener = EventListenerTouchAllAtOnce::create();
//    listener->onTouchesBegan = CC_CALLBACK_2(SneakyJoystick::onTouchesBegan,this);
//    listener->onTouchesMoved = CC_CALLBACK_2(SneakyJoystick::onTouchesMoved, this);
//    listener->onTouchesEnded = CC_CALLBACK_2(SneakyJoystick::onTouchesEnded, this);
//    listener->onTouchesCancelled = CC_CALLBACK_2(SneakyJoystick::onTouchesCancelled, this);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(SneakyJoystick::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SneakyJoystick::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SneakyJoystick::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

//void SneakyJoystick::onTouchesBegan(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event)
bool SneakyJoystick::onTouchBegan(Touch *touch, cocos2d::Event *event)
{
    //    Vector<Touch*>::const_iterator touchIter = touch.begin();
    //    while(touchIter != touch.end())
    //    {
    //        Touch *pTouch = (Touch*)(*touchIter);
    Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
    //if([background containsPoint:[background convertToNodeSpace:location]]){
    location = this->convertToNodeSpace(location);
    //Do a fast rect check before doing a circle hit check:
    if(location.x < -joystickRadius || location.x > joystickRadius || location.y < -joystickRadius || location.y > joystickRadius){
        return false;
    }else{
        float dSq = location.x*location.x + location.y*location.y;
        if(joystickRadiusSq > dSq){
            this->updateVelocity(location);
            return true;
        }
        //        }
        //        touchIter++;
    }
    return true;
}

//void SneakyJoystick::onTouchesMoved(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event)
void SneakyJoystick::onTouchMoved(Touch *touch, cocos2d::Event *event)
{
//    Vector<Touch*>::const_iterator touchIter = touch.begin();
//    while(touchIter != touch.end())
//    {
//        Touch *pTouch = (Touch*)(*touchIter);
        Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
        location = this->convertToNodeSpace(location);
        this->updateVelocity(location);
//        touchIter++;
//    }
}

//void SneakyJoystick::onTouchesEnded(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event)
void SneakyJoystick::onTouchEnded(Touch *touch, cocos2d::Event *event)
{
//    Vector<Touch*>::const_iterator touchIter = touch.begin();
//    while(touchIter != touch.end())
//    {
//        Touch *pTouch = (Touch*)(*touchIter);
        Point location = Vec2(0,0);
        if(!autoCenter){
            Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
            location = this->convertToNodeSpace(location);
        }
        this->updateVelocity(location);
//        touchIter++;
//    }
}

//void SneakyJoystick::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event)
void SneakyJoystick::onTouchCancelled(Touch *touch, cocos2d::Event *event)
{
//    this->onTouchesEnded(touch, event);
     this->onTouchEnded(touch, event);
}