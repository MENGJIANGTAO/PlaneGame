//
//  Player.cpp
//  TestApp
//
//  Created by Mengjiangtao on 7/8/15.
//
//

#include "Player.h"
#include "World.h"

Player *Player::createPlayer(const char *fileName)
{
    Player *player = new Player();
    if(player && player->initWithFile(fileName))
    {
        player->autorelease();
        player->playerInit(fileName);
        return  player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

void Player::playerInit(const char *fileName)
{
    Size size = Director::getInstance()->getWinSize();
    this->setPosition(Vec2(size.width*0.5,this->getContentSize().height*0.5));
    this->createAnimate(fileName);
    hpMax = 3;
    hp = 3;
    score = 0;
    strongTime = 5*60;
    
    for(int i = 1;i<=hp;i++)
    {
        Sprite *spHp = Sprite::create("icon_hp.png");
        spHp->setPosition(Vec2(size.width-25*i,this->getContentSize().height*0.5));
        if(i==1){
            spHp->setTag(tag_playerHp1);
        }else if(i == 2){
            spHp->setTag(tag_playerHp2);
        }else if(i==3){
            spHp->setTag(tag_playerHp3);
        }
        World::shareWorld()->addChild(spHp,10);
    }
    
    Label *label = Label::createWithSystemFont("Blood:","helvetica",24);
    label->setPosition(Vec2(30,size.height-22));
    World::shareWorld()->addChild(label);
    
    string strScore = Convert2String(score);
    Label* labelScores = Label::createWithSystemFont(strScore.c_str(), "helvetica", 24);
    labelScores->setPosition(Vec2(110,size.height-22));
    labelScores->setColor(Color3B(255, 255, 0));
    World::shareWorld()->addChild(labelScores,10,tag_scoreTTF);
    
    Label* labelKill = Label::createWithSystemFont("Kill:", "helvetica", 24);
    labelKill->setPosition(Vec2(30,size.height-52));
    World::shareWorld()->addChild(labelKill,10);
    
    std::string strKillCount=Convert2String(killCount);
    strKillCount+="/100";
    Label* labelKillCount = Label::createWithSystemFont(strKillCount.c_str(), "helvetica", 24);
    labelKillCount->setPosition(Vec2(110,size.height-52));
    labelKillCount->setColor(Color3B(255, 255, 0));
    World::shareWorld()->addChild(labelKillCount,10,tag_killsCountTTF);
    
}

void Player::addScore(int _value){
    score+=_value;
    std::string strScore=Convert2String(score);
    Label* ttf = (Label*)World::shareWorld()->getChildByTag(tag_scoreTTF);
    ttf->setString(strScore.c_str());
}

void Player::addKillCount(int _value)
{
    killCount+=_value;
    std::string strKillCount=Convert2String(killCount);
    strKillCount+="/100";
    Label* ttf = (Label*)World::shareWorld()->getChildByTag(tag_killsCountTTF);
    ttf->setString(strKillCount.c_str());
    int oldScore =atoi(UserDefault::getInstance()->getStringForKey("user_score1","-1").c_str());
    if(score>oldScore){
        UserDefault::getInstance()->setStringForKey("user_score1", Convert2String(score));
        UserDefault::getInstance()->flush();
        //            World::shareWorld()->isGetNewRecord = true;
    }
    
    //        if(killCount>=100)
    //            World::shareWorld()->winGame();
}


void Player::downHp(){
    if(isStrong){
        return;
    }
    hp-=1;
    
    if(hp<=0){
        this->setVisible(false);
        isDead=true;
        
//        World::shareWorld()->lostGame();
    }else{
        switch (hp) {
            case 1:
                World::shareWorld()->removeChildByTag(tag_playerHp2, true);
                break;
                
            case 2:
                World::shareWorld()->removeChildByTag(tag_playerHp3, true);
                break;
        }
        isStrong=true;
        strongCount=0;
        this->schedule(schedule_selector(Player::strongIng));
    }
}

void Player::strongIng(float dt){
    strongCount++;
    if(strongCount>=strongTime){
        this->setVisible(true);
        isStrong=false;
        this->unschedule(schedule_selector(Player::strongIng));
    }else{
        if(strongCount%2==0){
            this->setVisible(false);
        }else{
            this->setVisible(true);
        }
    }
}

void Player::createAnimate(const char *fileName)
{
    Animation* animation = Animation::create();
    Texture2D* texture = TextureCache::getInstance()->addImage(fileName);
    int eachWidth = this->getContentSize().width/5;
    for(int i = 0;i<5;i++)
    {
        animation->addSpriteFrameWithTexture(texture, Rect(i*eachWidth,0,eachWidth,this->getContentSize().height));
    }
    animation->setDelayPerUnit(0.2f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(-1);
    Animate *animate = Animate::create(animation);
    this->runAction(animate);
}