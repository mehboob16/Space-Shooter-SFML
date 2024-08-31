#include "AddOn.cpp"


class Danger:public AddOn{
public:

    Danger(float x = -100, float y= -100, std:: string img_path = "img/pill_red.png"):AddOn(img_path, x,y){
        type = 3;
    }

    Bullet* fire(float x, float y){
        return nullptr;
    }
    bool live(){return false;}
    bool danger(){return true;}
    void powerUp(float x, float y){}
};