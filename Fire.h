#include "AddOn.cpp"


#ifndef FIRE_H_
#define FIRE_H_
class Fire:public AddOn{
public:
    Fire(float x = -100, float y= -100, std:: string img_path = "img/bolt_bronze.png"):AddOn(img_path, x,y){
        type = 1;
    }

    Bullet* fire(float x, float y){
        Bullet* b = new Bullet(x,y, "img/laserRed02.png");
        return b;
    }
    bool live(){return false;}
    bool danger(){return false;}
    void powerUp(float x, float y){}
};

#endif