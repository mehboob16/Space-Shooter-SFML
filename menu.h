
#include "game.cpp"
#include <SFML/Audio.hpp>
class Menu
{
    Sprite background; // Game background sprite
    Texture bg_texture;
    highScore file;
    Font font;
    bool musicPlay;
    SoundBuffer buffer;
    std::string name;

    Sound sound;

public:
    // add menu attributes here
    Menu();
    void display_menu();
    void instructionUi(RenderWindow &window);
    void playMusic();
    bool startGameUi(RenderWindow &window);
    int getRank(string na);
};
