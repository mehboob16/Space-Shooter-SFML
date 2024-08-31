#include "Enemy.h"
#include "Bomb.h"
#include <iostream>

#ifndef INVADOR_H_
#define INVADOR_H_

class Invador : public Enemy
{
public:
	Invador( Bomb *bmb, int lev, std::string img_path, float x, float y);
	void bomb(float time);
	bool collision(Sprite sprite);
};

#endif