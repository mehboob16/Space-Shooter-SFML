#include "Invador.h"

#ifndef INVADOR_CPP_
#define INVADOR_CPP_
Invador::Invador(Bomb *bmb, int lev, std::string img_path, float x, float y) : Enemy(img_path, x, y)
{
    b = bmb;
    bOnScreen = false;
    level = lev;
}

void Invador::bomb(float time)
{
    timer += time;

    if (bOnScreen)
    {
        b->move();
        if (b->y_pos > sizey)
        {
            bOnScreen = false;
        }
    }
    else if (timer > rate)
    {
        timer = 0;
        if (bOnScreen)
            delete b;
        b = new Bomb(level, x_pos + spWidth / 2 - 20, y_pos + spHeight);
        bOnScreen = true;
    }
}
bool Invador::collision(Sprite sprite)
{ // returns 1 if collision with spaceship, 2 if collision with bullet, 0 if no collision occurs
    // collision with spaceship
    float px = sprite.getGlobalBounds().left, py = sprite.getGlobalBounds().top;
    float h = sprite.getGlobalBounds().height, w = sprite.getGlobalBounds().width;

    if (((px >= x_pos && px <= x_pos + spWidth) || (px + w >= x_pos && px + w <= x_pos + spWidth)) && ((py >= y_pos && py <= y_pos + spHeight) || (py + h >= y_pos && py + h <= y_pos + spHeight)))
        return true;

    return false;
}

#endif