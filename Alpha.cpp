#include "Alpha.h"
bool Alpha:: seeded = false;


Alpha:: Alpha(Bomb *bmb, int lev, float x , float y, std::string img_path ) : Invador(bmb, lev, img_path, x, y)
{
    sprite.setScale(0.6, 0.6);
    spHeight = 106 * 0.6;
    spWidth = 125 * 0.6;

    rate = 5;
    if (!seeded)
    {
        srand(time(0));
        seeded = true;
    }
    timer = (int)(rand()) % (int)rate;      //assigning timer random value bombs are randomly generated
    points = 10;
}