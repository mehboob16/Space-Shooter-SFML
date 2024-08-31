#include <SFML/Graphics.hpp>
#include <string.h>
#include "Bullet.cpp"
#include "AddOn.h"
const int sizex = 350 * 1.5, sizey = 655;

using namespace sf;

class Player
{
	const short int spHeight = 107, spWidth = 103;
	float timer = 0, bulletRate = 1;

public:
	Texture tex;
	Sprite sprite;
	float speed = 0.5;
	float x, y;
	Bullet *b;
	AddOn *addon;
	bool addonbool;
	bool bOnScreen;
	int lives = 3;
	bool immortal;

	Player(std::string png_path, Bullet *bullet);
	void fire(float time);

	void move(std::string s);
	void wrapAround();
	bool collision(const Sprite &sprite);

	void addOnFunction();
	bool timeComplete();
	void immortalFunction(float time);
};
