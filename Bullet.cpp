#include "Bullet.h"

#ifndef BULLET_CPP_
#define BULLET_CPP_
Bullet::Bullet(float x , float y, std:: string img_path){
    
    tex.loadFromFile(img_path);
    sprite.setTexture(tex);
    x_pos= x ;  y_pos = y;
    
    sprite.setPosition(x_pos, y_pos);

}
void Bullet::move(float x, float y){
    

    float delta_y = y, delta_x = x;

    delta_y*=speed, delta_x *= speed;

    y_pos+=delta_y;
    x_pos+=delta_x;
    sprite.move(delta_x, delta_y);
}

#endif