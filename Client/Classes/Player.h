//
//  Player.h
//  TestApp
//
//  Created by Mengjiangtao on 7/8/15.
//
//

#ifndef __TestApp__Player__
#define __TestApp__Player__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

typedef enum{
    tag_player,
    tag_playerHp1,
    tag_playerHp2,
    tag_playerHp3,
    tag_scoreTTF,
    tag_killsCountTTF,
    tag_uniqueSkill1,
    tag_uniqueSkill2,
    tag_uniqueSkill3,
}tagPlayer;

template<typename T>
string Convert2String(const T &value)
{
    stringstream ss;
    ss<<value;
    return ss.str();
}
class Player:public cocos2d::Sprite
{
public:
    static Player* createPlayer(const char* fileName);
    int hp;
    int hpMax;
    int score;
    int killCount;
    bool isDead;
    
    void downHp();
    void addScore(int _value);
    void addKillCount(int _value);
private:
    float strongTime;
    int strongCount;
    bool isStrong;
    
    void strongIng(float dt);
    void playerInit(const char* fileName);
    void createAnimate(const char* fileName);
};

#endif /* defined(__TestApp__Player__) */
