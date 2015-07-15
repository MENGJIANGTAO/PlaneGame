//
//  Enemy.cpp
//  TestApp
//
//  Created by Mengjiangtao on 7/9/15.
//
//

#include "Enemy.h"
#include "World.h"

Enemy* Enemy::createEnemy(const char* fileName,int _type,int _way){
    Enemy* enemy = new Enemy();
    if(enemy && enemy->initWithFile(fileName)){
        enemy->autorelease();
        enemy->enemyInit(fileName,_type,_way);
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}

void Enemy::enemyInit(const char* fileName,int _type,int _way){
    way=0;
    createAnimate(fileName, 10);
    Size size = Director::getInstance()->getWinSize();
    if(_type==0)
    {
        scoreValue=1;
        hp = 1;
    }else if(_type==1)
    {
        scoreValue=2;
        hp = 3;
    }else if (_type == 2)
    {
        scoreValue=3;
        hp = 8;
    }
    this->setPosition(Vec2(CCRANDOM_0_1()*size.width,size.height+this->getContentSize().height));
    this->scheduleUpdate();
}


void Enemy::update(float time){
    CallFunc *func = CallFunc::create(this, CC_CALLFUNC_SELECTOR(Enemy::removeSelf));
    switch (way) {
        case 0:{
            this->setPosition(this->getPosition()+Vec2(0,-2.5f));
            break;
        }
        case 1:{
            if(isActed){
                break;
            }
            isActed=true;
            this->runAction( Sequence::create(MoveTo::create(1, World::shareWorld()->getPlayer()->getPosition()),
                                                DelayTime::create(1.5),
                                                MoveTo::create(1, this->getPosition()),func,NULL));
            break;
        }
        case 2:
        {
            if(isActed){
                break;
            }
            isActed=true;
            this->runAction( Sequence::create(MoveTo::create(0.6,  World::shareWorld()->getPlayer()->getPosition()),DelayTime::create(3),
                                                MoveTo::create(0.6, this->getPosition()),func,NULL));
        }
            break;
    }
    if(this->getPositionY() < -this->getContentSize().height){
        //
        //        World::shareWorld()->getArrayForEnemy()->removeObject(this);
        World::shareWorld()->enemys.eraseObject(this);
        this->getParent()->removeChild(this,true);
    }
    
    Player * player = World::shareWorld()->getPlayer();
    if(!player->isDead){
        if(player->boundingBox().intersectsRect(this->boundingBox())){
            player->downHp();
        }
    }
}

void Enemy::removeSelf()
{
//    World::shareWorld()->getArrayForEnemy()->removeObject(this);
    World::shareWorld()->enemys.eraseObject(this);
//    log(World::shareWorld()->getVectorForEnemy().size());
    this->getParent()->removeChild(this,true);
    
}

void Enemy::createAnimate(const char* fileName,int allCount){
    
    Animation* animation = Animation::create();
    Texture2D * texture = TextureCache::getInstance()->addImage(fileName);
    int eachWidth=this->getContentSize().width/allCount;
    for (int i =0; i<allCount; i++)
    {
        animation->addSpriteFrameWithTexture(texture,Rect(i*eachWidth, 0, eachWidth, this->getContentSize().height));
    }
    animation->setDelayPerUnit(0.03f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(-1);
    Animate * animate = Animate::create(animation);
    this->runAction(animate);
}