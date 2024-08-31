#include "AddOn.h"

#ifndef ADDON_CPP_
#define ADDON_CPP_

AddOn::AddOn(std::string img_path, float x, float y)
{
    tex.loadFromFile(img_path);
    sprite.setTexture(tex);
    x_pos = x;
    y_pos = y;
    sprite.setPosition(x_pos, y_pos);
    timer = 0;
    bullets = nullptr;
    bulletsBool = nullptr;
}
void AddOn::move()
{
    y_pos += speed;
    sprite.move(0, speed);
}

#endif