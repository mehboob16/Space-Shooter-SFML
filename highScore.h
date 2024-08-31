#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iomanip>

using namespace sf;

#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

class highScore
{
    Sprite background; // Game background sprite
    Texture bg_texture;

    Sprite badge1, badge2, badge3;
    Texture b1, b2, b3;
    std::string name[10];
    int score[10];
    Font font;
    std:: string fileName;

public:
    highScore(std:: string str);
    void displayHighScore(RenderWindow& window);
    void readFile();
    void writeFile(std:: string n, int sco);
    std::string getName(int i);
    int getScore(int i);
};

#endif