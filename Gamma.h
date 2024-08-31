#include "Invador.cpp"
#include <time.h>

class Gamma: public Invador{
static bool seeded;
public:
    Gamma(Bomb* bmb, int lev, float x = -500, float y = -500, std:: string img_path = "img/enemy_3.png");
};
