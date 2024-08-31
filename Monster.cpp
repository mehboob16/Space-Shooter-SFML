#include "Monster.h"

Monster::Monster(int level, float x, float y, std::string img_path) : Enemy(img_path, x, y)
{
    spWidth = 655 * 0.5;
    spHeight = 655 * 0.5;

    sprite.setScale(0.5, 0.5);
    x_pos -= spWidth / 2;
    sprite.move(-spWidth / 2, 0);

    monstorTime = 5 * level;
    speed = 1.2 * level / (level + 1);
    rate = 2;
    fireTime = 0;
}
void Monster::bomb(float time)
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
            b = new Bomb(1, x_pos + sprite.getGlobalBounds().width / 2 - 10, y_pos + sprite.getGlobalBounds().height - 100, "img/laserBlue14.png");

            b->sprite.setScale(1, 10);

            bOnScreen = true;
            fireTime = 0;
        }
    }
    fireTime += time;
    timer += time;
}

bool Monster::collision(Sprite sprite)
{
    if (!bOnScreen)
        return false;

    float px = sprite.getGlobalBounds().left, py = sprite.getGlobalBounds().top;
    float h = sprite.getGlobalBounds().height, w = sprite.getGlobalBounds().width;

    float bh = b->sprite.getGlobalBounds().height, bw = b->sprite.getGlobalBounds().width;
    if (((b->x_pos >= px && b->x_pos <= px + w) || (b->x_pos + bw >= px && b->x_pos + bw <= px + w)) /*&& ((py >= b->y_pos && py <= b->y_pos + bh) || (py + h >= b->y_pos && py + h <= b->y_pos + bh))*/)
    {
        return true;
    }
    return false;
}

void Monster::move(int x)
{
    if (bOnScreen)
        return;
    if (x_pos + spWidth / 2 >= x && x_pos + spWidth / 2 >= 30)
    {
        x_pos -= speed;
        sprite.move(-speed, 0);
    }
    else if (x_pos + spWidth / 2 <= x && x_pos + spWidth / 2 <= 525)
    {
        x_pos += speed;
        sprite.move(speed, 0);
    }
}
int Monster::point()
{
    return 50;
}
bool Monster::timeComplete()
{
    return (timer >= monstorTime);
}