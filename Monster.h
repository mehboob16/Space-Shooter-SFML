#include "Enemy.h"

#ifndef MONSTER_H_
#define MONSTER_H_

class Monster : public Enemy
{
    float fireTime, speed = 0.5, monstorTime;

public:
    Monster(int level, float x = -500, float y = -500, std::string img_path = "img/monster1.png");
    void bomb(float time);
    bool collision(Sprite sprite);
    void move(int x);
    int point();
    bool timeComplete();
};

#endif