#include <SFML/Graphics.hpp>
#include <string.h>
#include "Bullet.cpp"
using namespace sf;

#ifndef ADDON_H_
#define ADDON_H_

class AddOn
{
protected:
    float spWidth, spHeight, speed = 0.1;

public:
    int type; // 1 for fire, 2 live, 3 danger, 4 powerup
    Texture tex;
    Sprite sprite;
    float x_pos, y_pos, timer;
    Bullet **bullets;
    bool *bulletsBool;

    AddOn(std::string img_path, float x, float y);
    void move();
    virtual Bullet *fire(float x, float y) = 0; //constructs fire type bullet and returns it
    virtual bool live() = 0;    
    virtual bool danger() = 0;
    virtual void powerUp(float x, float y) = 0; //makes 7 bullets and fires them in different direction
};

#endif