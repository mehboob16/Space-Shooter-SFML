#include "Enemy.h"

#ifndef DRAGON_H_
#define DRADON_H_

class Dragon : public Enemy
{
    float fireTime;
    short int range; //1 for downleft, 0 for down, -1 downright
public:
    Dragon(float x = 5000, float y = 5000, std::string img_path = "img/dragon1.png");
    //constructes dragon at top-middle of the screen

    void bomb(float time);
    void bomb(float time, int type); //fires in different direction
    bool collision(Sprite sprite);  //returns true if sprite is inside fire of dragon
    float getTime();    //returns total time of dragon on screen
    void setTime(float time); //sets timer 
};

#endif