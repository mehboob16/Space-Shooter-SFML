
#include <SFML/Graphics.hpp>
#include <string.h>
#include "Bomb.cpp"

using namespace sf;

#ifndef ENEMY_H_
#define ENEMY_H_

class Enemy
{
protected:
    float timer, rate, spWidth, spHeight, points;
    int level;

public:
    bool bOnScreen = false;
    Bomb *b;

    float x_pos, y_pos;
    Texture tex;
    Sprite sprite;

    Enemy(){}
    Enemy(std::string img_path, float x, float y)
    {
        tex.loadFromFile(img_path);
        sprite.setTexture(tex);
        x_pos = x;
        y_pos = y;
        sprite.setPosition(x_pos, y_pos);
    }
    
    virtual void bomb(float time) = 0;
    
    virtual bool collision(Sprite sprite) = 0;
    
    virtual bool timeComplete(){
        return false;
    }
    virtual void move(int x){}
    virtual int point(){
        return points;
    }
};

#endif