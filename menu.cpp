#include "menu.h"

// add menu attributes here
Menu::Menu() : file("highscore.txt")
{
    musicPlay = false;
    bg_texture.loadFromFile("img/background.png");
    background.setTexture(bg_texture);
    background.setScale(1.5, 1);
    font.loadFromFile("font/Pacifico.ttf");
    buffer.loadFromFile("sound/music.wav");
    // constructors body
}

void Menu::display_menu()

{

    RenderWindow window(VideoMode(sizex, sizey), title, (Style::Titlebar | Style::Close));
    Texture obj2;
    file.readFile();
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    obj2.loadFromFile("img/buttonRed.png");

    sound.setBuffer(buffer);
    sound.setVolume(50.f);

    Sprite button(obj2);

    Text text;
    text.setCharacterSize(25);

    while (window.isOpen())
    {
        text.setFillColor(Color::Black);
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            else if (e.type == Event::MouseButtonPressed)
            {

                if (e.mouseButton.button == Mouse::Left)
                {

                    int x_pos = Mouse::getPosition(window).x; // getting coordinates of mouse if left key pressed
                    int y_pos = Mouse::getPosition(window).y;

                    if (x_pos > 150 && x_pos < 150 + 229) // if mouse above start button
                    {
                        if (y_pos > 150 && y_pos < 150 + 39)
                        {
                            if (startGameUi(window))
                            {
                                Game g(name, getRank(name));

                                g.start_game(window);
                            }
                        }
                        else if (y_pos > 250 && y_pos < (250 + 39))
                        {

                            file.displayHighScore(window);
                        }

                        else if (y_pos > 350 && y_pos < 350 + 39)
                        {
                            musicPlay = !musicPlay;
                            playMusic();
                        }
                        else if (y_pos > 450 && y_pos < 450 + 39)
                            instructionUi(window);
                    }
                }
            }
        }
        window.clear(Color::Black);
        window.draw(background);
        button.setPosition(150, 150);
        window.draw(button);
        button.setPosition(150, 250);
        window.draw(button);
        button.setPosition(150, 350);
        window.draw(button);
        button.setPosition(150, 450);
        window.draw(button);

        text.setFont(font);
        text.setStyle(Text::Bold);
        text.setString("New Game");
        text.setPosition(200, 155);
        // Draw it
        window.draw(text);

        text.setString("High Scores");
        text.setPosition(180, 255);
        window.draw(text);

        text.setString("Sound");
        text.setPosition(220, 355);
        window.draw(text);

        text.setString("Instruction");
        text.setPosition(200, 455);
        window.draw(text);
        window.display();
    }

    // display menu screen here

    // add functionality of all the menu options here

    // if Start game option is chosen
}

void Menu::instructionUi(RenderWindow &window)
{
    Texture tex;
    tex.loadFromFile("img/instruction.jpeg");
    Sprite img(tex);

    Text text;
    text.setCharacterSize(30);

    window.clear(Color::Black);
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            else if (e.type == Event::MouseButtonPressed)
            {

                if (e.mouseButton.button == Mouse::Left)
                {

                    int x_pos = Mouse::getPosition(window).x; // getting coordinates of mouse if left key pressed
                    int y_pos = Mouse::getPosition(window).y;

                    if (x_pos > 10 && x_pos < 10 + 90) // if mouse above start button
                    {
                        if (y_pos > 600 && y_pos < 600 + 30)
                        {
                            return;
                        }
                    }
                }
            }
        }

        img.setScale(0.35, 0.7);
        img.setPosition(0, 0);
        window.draw(img);

        text.setFont(font);
        text.setStyle(Text::Bold);
        text.setFillColor(Color::Black);
        text.setString("<Back");
        text.setPosition(10, 600);

        window.draw(text);

        window.display();
    }
}
void Menu::playMusic()
{
    if (musicPlay)
    {
        sound.play();
        sound.setLoop(true);
    }
    else
        sound.pause();
}

bool Menu::startGameUi(RenderWindow &window)
{
    name = "";
    Text text;
    text.setCharacterSize(40);
    text.setFillColor(Color::White);

    while (window.isOpen())
    {

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            else if (e.type == Event::MouseButtonPressed)
            {

                if (e.mouseButton.button == Mouse::Left)
                {

                    int x_pos = Mouse::getPosition(window).x; // getting coordinates of mouse if left key pressed
                    int y_pos = Mouse::getPosition(window).y;

                    if (x_pos > 10 && x_pos < 100 && y_pos > 550 && y_pos < 550 + 39) // if mouse above start button
                    {
                        return false;
                    }
                }
            }
            else if (e.type == Event::TextEntered)
            {
                if (e.text.unicode < 128)
                {
                    if (e.text.unicode == '\r') // enter pressed
                        return true;
                    else if (e.text.unicode == '\b' && !name.empty())
                    {
                        name.pop_back();
                    }
                    else if (e.text.unicode != '\b') //'\b' is for backspace
                    {
                        name += (char)(e.text.unicode);
                    }
                }

                text.setString(name);
            }
        }

        window.clear(Color::Black);
        window.draw(background);

        text.setFont(font);
        text.setStyle(Text::Bold);

        text.setString(name);
        text.setPosition(100, 300);
        window.draw(text);

        text.setString("<Back");
        text.setPosition(10, 550);
        // Draw it
        window.draw(text);

        text.setString("Enter Name:");
        text.setPosition(140, 200);
        window.draw(text);

        window.display();
    }
    return false;
}
int Menu::getRank(string na)
{
    for (int i = 0; i < 3; i++)
    {
        if (file.getName(i) == na)
            return i + 1;
    }
    return -1;
}