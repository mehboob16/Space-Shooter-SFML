#include "Invador.cpp"
#include <time.h>


class Alpha: public Invador{
static bool seeded;
public:
    Alpha(Bomb* bmb,int lev, float x = -500, float y= -500, std:: string img_path = "img/enemy_1.png");
};
