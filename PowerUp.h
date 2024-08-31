#include "AddOn.cpp"

class PowerUp : public AddOn
{
public:
    PowerUp(float x = -100, float y = -100, std::string img_path = "img/powerupBlue_bolt.png");

    Bullet *fire(float x, float y);
    bool live();
    bool danger();
    void powerUp(float x, float y);
    ~PowerUp();
};