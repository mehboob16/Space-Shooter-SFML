#include "Bomb.h"

#ifndef ENEMY_CPP_
#define ENEMY_CPP_
Bomb::Bomb(int level, float x , float y, std::string img_path)
{
    tex.loadFromFile(img_path);
    sprite.setTexture(tex);
    x_pos = x;
    y_pos = y;
    sprite.setPosition(x_pos, y_pos);
    sprite.setScale(1, 1);

    speed = 0.5 * level / (level + 4);
}

void Bomb::move()
{
    y_pos += speed;
    sprite.setPosition(x_pos, y_pos);
}

#endif