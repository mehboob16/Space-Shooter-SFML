#include "Dragon.h"



Dragon::Dragon(float x, float y , std::string img_path) : Enemy(img_path, x, y)
{
    spWidth = 240;
    spHeight = 240;

    x_pos -= spWidth / 2;
    sprite.move(-spWidth / 2, 0);

    rate = 2;
    fireTime = 0;
    timer = 0;
}
void Dragon::bomb(float time)
{
    bomb(time, 0);
}
void Dragon::bomb(float time, int type)
{
    if (bOnScreen)
    {
        if (fireTime > rate)
        {
            delete b;
            bOnScreen = false;
            fireTime = 0;
        }
    }
    else
    {
        if (fireTime > rate)
        {
            b = new Bomb(1, x_pos + sprite.getGlobalBounds().width / 2, y_pos + sprite.getGlobalBounds().height - 20, "img/dragonFire.png");
            b->x_pos -= b->sprite.getGlobalBounds().width / 2;
            b->sprite.setPosition(b->x_pos, b->y_pos);
            range = type;

            b->sprite.rotate(range * 23);
            bOnScreen = true;
            fireTime = 0;
        }
    }
    fireTime += time;
    timer += time;
}

bool Dragon::collision(Sprite sprite)
{
    if (!bOnScreen)
        return false;
    if (range == 0)
    {
        float px = sprite.getGlobalBounds().left, py = sprite.getGlobalBounds().top;
        float h = sprite.getGlobalBounds().height, w = sprite.getGlobalBounds().width;

        float x = b->x_pos + b->sprite.getGlobalBounds().width / 2 - 30;
        if (((px >= x && px <= x + 60) || (px + w >= x && px + w <= x + 60)) && ((py >= b->y_pos && py <= b->y_pos + b->sprite.getGlobalBounds().height) || (py + h >= b->y_pos && py + h <= b->y_pos + b->sprite.getGlobalBounds().height)))
        {

            return true;
        }

        return false;
    }
    else if (range == -1 || range == 1)
    {
        float x1 = b->x_pos + b->sprite.getGlobalBounds().width / 2, y1 = y_pos, x2, y2 = 650; // position of top middle of fire

        if (range == 1)
            x2 = 30;
        else
            x2 = 495;

        float slope = (y2 - y1) / (x2 - x1);

        // for(int i=0 ; i<x1 ; i++){
        //     j = -slope*(i);

        // }
        float spx = sprite.getPosition().x, spy = sprite.getPosition().y;
        float spx1 = sprite.getGlobalBounds().width + spx, spy1 = sprite.getGlobalBounds().height + spy;
        if (((spy-y1) - slope * (spx-x1) <= 30 && (spy-y1) - slope * (spx-x1) >= -30) || ((spy1-y1) - slope * (spx1-x1) <= 30 && (spy1-y1) - slope * (spx1-x1) >= -30) || ((spy1-y1) - slope * (spx-x1) <= 30 && (spy1-y1) - slope * (spx1-x1) >= -30) || ((spy-y1) -  slope * (spx1-x1) <= 30 && (spy1-y1) - slope * (spx1-x1) >= -30))
        {
            return true;
        }

        return false;
    }
    return false;
}

float Dragon:: getTime(){
    return timer;
}
void Dragon::setTime(float time){
    timer = time;
}