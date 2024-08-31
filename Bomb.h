#include <SFML/Graphics.hpp>
#include<string.h>

using namespace sf;

#ifndef BOMB_H_
#define BOMB_H_

class Bomb{
public:
    Texture tex; Sprite sprite;
    float speed = 0.5, x_pos, y_pos;

    Bomb(int level =1,float x = 1000, float y = 1000, std:: string img_path = "img/enemy_laser.png");
void move();

};
#endif