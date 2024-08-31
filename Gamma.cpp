#include "Gamma.h"

bool Gamma:: seeded = false;

Gamma::Gamma(Bomb *bmb, int lev, float x , float y , std::string img_path) : Invador(bmb, lev, img_path, x, y)
{
    sprite.setScale(0.5, 0.5);
    spHeight = 132 * 0.4;
    spWidth = 173 * 0.4;

    rate = 2;

    if (!seeded)
    {
        srand(time(0));
        seeded = true;
    }
    timer = (int)rand() % (int)rate;
    points = 30;
}