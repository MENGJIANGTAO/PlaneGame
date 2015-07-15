//
//  Bullet.cpp
//  TestApp
//
//  Created by Mengjiangtao on 7/9/15.
//
//

#include "Bullet.h"
#include "World.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Bullet* Bullet::createBullet(const char* _fileName,float _speed,Point _position){
    Bullet* bullet = new Bullet();
    if(bullet && bullet->initWithFile(_fileName)){
        bullet->autorelease();
        bullet->bulletInit(_speed,_position);
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return NULL;
}
void Bullet::bulletInit(float _speed,Point _position){
    speed = _speed;
    this->setPosition(_position);
    this->scheduleUpdate();
}

void Bullet::update(float time){
    this->setPosition(this->getPosition()+Vec2(0,speed));
    
    if(this->getPositionY() > Director::getInstance()->getWinSize().height)
    {
        this->removeFromParentAndCleanup(true);
        return;
    }
    
//    Vector<Enemy*> vector = World::shareWorld()->enemys;
//    for (int i =0; i<vector.size();i++) {
//    for(auto it = World::shareWorld()->enemys.begin();it!=World::shareWorld()->enemys.end();){
    for(auto it : World::shareWorld()->enemys){
//        Enemy* enemy = *it;
        if(it->boundingBox().intersectsRect(this->boundingBox()))
        {
            it->hp--;
            if(it->hp <= 0)
            {
                SimpleAudioEngine::getInstance()->playEffect("effect_boom.mp3");
                
                ParticleSystemQuad * particle = ParticleSystemQuad::create("particle_boom.plist");
                particle->setPosition(it->getPosition());
                particle->setAutoRemoveOnFinish(true);
                World::shareWorld()->addChild(particle);
                World::shareWorld()->getPlayer()->addScore(it->scoreValue);
                World::shareWorld()->getPlayer()->addKillCount(1);
                World::shareWorld()->enemys.eraseObject(it);
                World::shareWorld()->removeChild(it, true);
                break;
            }else
            {
                this->removeFromParentAndCleanup(true);
                break;
            }
        }
    }
}

void Bullet::onExit(){
    this->unscheduleUpdate();
    Sprite::onExit();
}