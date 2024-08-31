#include <SFML/Graphics.hpp>
#include<string.h>

using namespace sf;
#ifndef BULLET_H_
#define BULLET_H_
class Bullet{
const short int spHeight = 13, spWidth = 37;
public:
Texture tex;
Sprite sprite;
float speed = 0.6, x_pos, y_pos;

Bullet(float x = -50 , float y = -50, std:: string img_path = "img/laserGreen04.png");
void move(float x = 0, float y = -1);


};

#endif