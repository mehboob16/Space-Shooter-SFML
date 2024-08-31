#include "player.h"

Player::Player(std::string png_path, Bullet *bullet)
{

    tex.loadFromFile(png_path);
    sprite.setTexture(tex);
    x = sizex / 2;
    y = sizey - spHeight;
    sprite.setPosition(x, y);
    sprite.setScale(0.75, 0.75);

    b = bullet;
    bOnScreen = true;
    addonbool = false;
    immortal = false;
}
void Player::fire(float time)
{
    timer += time;

    if (bOnScreen)
    {
        b->move();

        if (b->y_pos < -37)
        {
            bOnScreen = false;
        }
    }
    else if (timer > bulletRate)
    {
        timer = 0;
        delete b;

        if (addonbool)
        {

            if (addon->type == 1)
            {
                b = addon->fire(x + spWidth / 2 - 18, y);
            }
            else
            {
                b = new Bullet(x + spWidth / 2 - 18, y, "img/laserGreen04.png");
            }
        }
        else
        {
            b = new Bullet(x + spWidth / 2 - 18, y, "img/laserGreen04.png");
        }
        bOnScreen = true;
    }
}
void Player::move(std::string s)
{
    float delta_x = 0, delta_y = 0;
    if (s == "l")
        // move the player left
        delta_x = -1;
    else if (s == "r")
        // move the player right
        delta_x = 1;
    if (s == "u")
        delta_y = -1;
    else if (s == "d")
        delta_y = 1;

    delta_x *= speed;
    delta_y *= speed;
    x += delta_x;
    y += delta_y;
    sprite.move(delta_x, delta_y);
}
void Player::wrapAround()
{
    // std::cout<<bOnScreen<<std::endl;
    if (x < 0 - spWidth / 2)
    {
        x = sizex - (spWidth / 2) + 1; // horizontal size of screen
    }
    else if (x > sizex - spWidth / 2 + 1)
        x = 0 - spWidth / 2;
    if (y < 0 - spHeight / 2)
        y = sizey - spHeight / 2;
    else if (y > sizey - spHeight / 2)
        y = 0 - spHeight / 2;
    sprite.setPosition(x, y);
}

bool Player::collision(const Sprite &sprite)
{
    // collision with bomb
    float bx = sprite.getGlobalBounds().left, by = sprite.getGlobalBounds().top;
    float h = sprite.getGlobalBounds().height, w = sprite.getGlobalBounds().width;

    if (((bx >= x + 20 && bx <= x + spWidth - 20) || (bx + w >= x + 20 && bx + w <= x + spWidth - 20)) && ((by >= y + 20 && by <= y + spHeight) || (by + h >= y + 20 && by + h <= y + spHeight)))
        return true;
    return false;
}

void Player::addOnFunction()
{
    if (!addonbool)
        return;
    if (addon->live())
    {
        lives++;
        delete addon;
        addon = nullptr;
        addonbool = false;
        // std:: cout <<addonbool <<std:: endl;
    }
    else if (addon->danger())
    {
        lives--;
        delete addon;
        addon = nullptr;
        addonbool = false;
        // std:: cout << addonbool << std:: endl;
    }
    else if (addon->type == 1)
    {
        delete b;
        b = addon->fire(x, y);
        bOnScreen = true;
    }
    else if (addon->type)
    {
        immortal = true;
    }
}
bool Player::timeComplete()
{
    return false;
}
void Player::immortalFunction(float time)
{
    static float time1 = 0;

    if (!immortal)
        return;

    time1 += time;

    if (time1 > 4 && !addonbool)
    {
        immortal = false;
        time1 = 0;
    }
    else if (time1 > 4 && addon->type != 4)
    {
        immortal = false;
        time1 = 0;
    }
}