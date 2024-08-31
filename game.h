
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include "highScore.cpp"
#include "player.cpp"
//enemys
#include "Alpha.cpp"
#include "Beta.cpp"
#include "Gamma.cpp"
#include "Monster.cpp"
#include "Dragon.cpp"
//addons
#include "Fire.h"
#include "Lives.h"
#include "PowerUp.cpp"
#include "Danger.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
int level , phase, numOfEnemies;
long int score;
Font font;
highScore file;
std:: string name;
int rank;
Bullet* bullet;
Enemy** enemies;
Bomb** bombs;
bool* enemiesBool;
AddOn** addon;
int addonNum;
bool pause;
Sprite badge;
Texture badge_tex;
Dragon* dragon;
bool draBool;
public:
Sprite background; //Game background sprite
Texture bg_texture;
Player* p; //player 
// add other game attributes



Game(string n, int r);
void start_game(RenderWindow& window); 
void makeEnemy();   //makes shapes according to level and phase
void drawEnemiesAndPlayer(RenderWindow& window); //draws invadors and its bombs   
void enemyBomb(float time); //bomb functionallities of invadors
void collision();   //checks all collision among bomb-player, invador-player , bullet-invador and deletes enemies,bullets, bombs if collided, decreases live of player
bool gameOver();     //returns weather game is over or not 
void gameOverUi(RenderWindow& window);  //game over screen
void changeLevel(RenderWindow& window); // changes level and calls makeEnemy();
void addOnFunction(float time); //all functionalities of addOns(giving player addons and taking it back)
void showPoints(RenderWindow& window);  
void levelChangeAnimation(RenderWindow& window);  

void dragonFunctions(float time);   // calls all functionallities of dragon(fire, collision)

~Game();
};

