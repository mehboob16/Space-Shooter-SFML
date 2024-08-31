#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, std::string img_path) : AddOn(img_path, x, y)
{
    type = 4;
    bullets = new Bullet *[7];
    bulletsBool = new bool[7];
    for (int i = 0; i < 7; i++)
    {
        bulletsBool[i] = false;
        bullets[i] = new Bullet;
    }
}

Bullet* PowerUp::fire(float x, float y)
{
    return nullptr;
}
bool PowerUp::live() { return false; }
bool PowerUp::danger() { return false; }
void PowerUp::powerUp(float x, float y)
{
    bool move = false;
    for (int i = 0; i < 7; i++)
    {
        if (bulletsBool[i])
        {
            move = true;
            break;
        }
    }
    if (move)
    {
        for (int i = 0; i < 7; i++)
        {
            bullets[i]->move(-0.3 + i * 0.1);

            if (bullets[i]->y_pos < -37 || bullets[i]->x_pos < -37 || bullets[i]->x_pos > 525)
            {
                bulletsBool[i] = false;
            }
        }
    }

    else
    {
        for (int i = 0; i < 7; i++)
        {
            delete bullets[i];
            bullets[i] = new Bullet(x + spWidth / 2 - 18, y, "img/laserGreen04.png");
            bulletsBool[i] = true;
        }
    }
}
PowerUp::~PowerUp()
{
    for (int i = 0; i < 7; i++)
    {
        delete bullets[i];
        /* code */
    }

    delete[] bullets;
    delete[] bulletsBool;
}