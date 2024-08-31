#include "Beta.h"

Beta::Beta(Bomb *bmb, int lev, float x, float y , std::string img_path) : Invador(bmb, lev, img_path, x, y)
{
    sprite.setScale(0.5, 0.5);
    spHeight = 154 * 0.5;
    spWidth = 120 * 0.5;

    rate = 3;
    if (!seeded)
    {
        srand(time(0));
        seeded = true;
    }
    timer = (int)(rand()) % (int)rate;
    points = 20;
}
bool Beta:: seeded = false;