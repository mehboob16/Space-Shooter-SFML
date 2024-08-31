#include "AddOn.cpp"


class Lives:public AddOn{
public:

    Lives(float x = -100, float y= -100, std:: string img_path = "img/pill_green.png"):AddOn(img_path, x,y){
        type = 2;
    }

    Bullet* fire(float x, float y){
        return nullptr;
    }
    bool live(){return true;}
    bool danger(){return false;}
    void powerUp(float x, float y){}
};