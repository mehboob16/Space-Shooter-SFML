#include "Invador.cpp"
#include <time.h>

class Beta: public Invador{
static bool seeded;
public:
    Beta(Bomb* bmb, int lev, float x = -500, float y = -500, std:: string img_path = "img/enemy_2.png");

};
