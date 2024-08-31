#include "game.h"
Game::Game(string n, int r) : file("highscore.txt")
{
    bullet = new Bullet;
    p = new Player("img/player_ship.png", bullet);
    bg_texture.loadFromFile("img/background.png");
    background.setTexture(bg_texture);
    background.setScale(1.5, 1);
    addonNum = -1;
    level = 1, phase = 1, score = 0;
    addon = new AddOn *[4]{ new Fire, new Lives, new Danger, new PowerUp };
    font.loadFromFile("font/Pacifico.ttf");
    dragon = new Dragon;
    name = n;
    pause = false;
    rank = r;
    draBool = false;

    //displaying badge according to rank of person playing
    switch (rank)
    {
    case 1:
        badge_tex.loadFromFile("img/star_gold.png");
        badge.setTexture(badge_tex);
        break;
    case 2:
        badge_tex.loadFromFile("img/star_silver.png");
        badge.setTexture(badge_tex);
        break;
    case 3:
        badge_tex.loadFromFile("img/star_bronze.png");
        badge.setTexture(badge_tex);
        break;
    default:
        break;
    }
    makeEnemy();
}
void Game::start_game(RenderWindow &window)
{
    srand(time(0));
    Clock clock;
    float timer = 0;

    levelChangeAnimation(window);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close();          // close the game
            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::P)
                    pause = !pause;
                else if (e.key.code == Keyboard::Escape)
                    return;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))  // If left key is pressed
            p->move("l");                            // Player will move to left
        if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            p->move("r");                            // player will move to right
        if (Keyboard::isKeyPressed(Keyboard::Up))    // If up key is pressed
            p->move("u");                            // playet will move upwards
        if (Keyboard::isKeyPressed(Keyboard::Down))  // If down key is pressed
            p->move("d");                            // player will move downwards

        ////////////////////////////////////////////////
        /////  Call your functions here            ////
        //////////////////////////////////////////////

        if (pause)
            continue;
        if (!draBool)
        {

            int temp = rand() % 80000;
            if (temp==50)
            {
                draBool = true;
            }
        }

        if (gameOver())
        {
            gameOverUi(window);
            return;
        }

        if (draBool)
        {
            dragonFunctions(time);
        }
        else
        {

            changeLevel(window);
            enemyBomb(time);

            if (phase != 4)
                collision();
            else
            {
                enemies[0]->move(p->x);
                if ((enemies[0]->collision(p->sprite) || p->collision(enemies[0]->sprite)) && !p->immortal)
                {
                    p->x = 230;
                    p->y = 560;
                    p->immortal = true;
                    p->lives--;
                }
            }
        }
        p->wrapAround();
        if (!p->addonbool)
        {
            p->fire(time);
        }
        else if (p->addon->type != 4)
            p->fire(time);
        else
        {
            p->b->y_pos = -40;
            p->addon->powerUp(p->x + p->sprite.getGlobalBounds().width / 2 + 10, p->y);
        }

        p->immortalFunction(time);
        addOnFunction(time);

        window.clear(Color::Black); // clears the screen
        window.draw(background);    // setting background
        showPoints(window);
        drawEnemiesAndPlayer(window);
        if (!p->addonbool)
        {
            if (p->bOnScreen)
                window.draw(p->b->sprite);
        }
        else if (p->addon->type != 4)
        {
            if (p->bOnScreen)
                window.draw(p->b->sprite);
        }
        else
        {
            for (int i = 0; i < 7; i++)
            {
                if (p->addon->bulletsBool[i])
                    window.draw(p->addon->bullets[i]->sprite);
            }
        }
        if (rank > 0)
        {
            badge.setPosition(490, 10);
            window.draw(badge);
        }
        window.display(); // Displying all the sprites
    }
}

void Game::makeEnemy()
{
    if (level == 1 && phase == 1)
    { // triangle
        numOfEnemies = 8;
        bombs = new Bomb *[numOfEnemies];
        for (int i = 0; i < numOfEnemies; i++)
        {
            bombs[i] = new Bomb;
        }
        enemies = new Enemy *[numOfEnemies];
        enemies[0] = new Alpha(bombs[0], level, 25, 250);
        enemies[1] = new Alpha(bombs[1], level, 125, 250);
        enemies[2] = new Alpha(bombs[2], level, 225, 250);
        enemies[3] = new Alpha(bombs[3], level, 325, 250);
        enemies[4] = new Alpha(bombs[4], level, 425, 250);
        enemies[5] = new Beta(bombs[5], level, 125, 150);
        enemies[6] = new Beta(bombs[6], level, 325, 150);
        enemies[7] = new Gamma(bombs[7], level, 225, 50);
    }
    else if (level == 1 && phase == 2)
    { // rectangle
        numOfEnemies = 12;
        bombs = new Bomb *[numOfEnemies];
        for (int i = 0; i < numOfEnemies; i++)
        {
            bombs[i] = new Bomb(level);
        }
        enemies = new Enemy *[12]
        { new Alpha(bombs[0], level, 25, 250), new Alpha(bombs[1], level, 125, 250), new Alpha(bombs[2], level, 225, 250), new Alpha(bombs[3], level, 325, 250), new Alpha(bombs[4], level, 425, 250), new Beta(bombs[5], level, 25, 150), new Beta(bombs[6], level, 25, 50), new Beta(bombs[7], level, 425, 150), new Beta(bombs[8], level, 425, 50), new Gamma(bombs[9], level, 125, 50), new Gamma(bombs[10], level, 225, 50) };
        enemies[11] = new Gamma(bombs[11], level, 325, 50);
    }
    else if (level == 1 && phase == 3)
    { // cross
        numOfEnemies = 12;
        bombs = new Bomb *[numOfEnemies];
        for (int i = 0; i < numOfEnemies; i++)
        {
            bombs[i] = new Bomb(level);
        }
        enemies = new Enemy *[12]
        { new Alpha(bombs[0], level, 25, 200), new Alpha(bombs[1], level, 150, 200), new Alpha(bombs[2], level, 300, 200), new Alpha(bombs[3], level, 425, 200), new Alpha(bombs[4], level, 175, 300), new Alpha(bombs[5], level, 300, 300), new Beta(bombs[6], level, 25, 100), new Beta(bombs[7], level, 150, 100), new Beta(bombs[8], level, 300, 100), new Beta(bombs[9], level, 425, 100), new Gamma(bombs[10], level, 150, 0), new Gamma(bombs[11], level, 300, 0) };
    }
    else if (level == 2 && phase == 1)
    { // diamond
        numOfEnemies = 10;
        bombs = new Bomb *[numOfEnemies];
        for (int i = 0; i < numOfEnemies; i++)
        {
            bombs[i] = new Bomb(level);
        }
        enemies = new Enemy *[numOfEnemies]
        { new Alpha(bombs[0], level, 25, 300), new Alpha(bombs[1], level, 125, 300), new Alpha(bombs[2], level, 225, 300), new Alpha(bombs[3], level, 325, 300), new Alpha(bombs[4], level, 425, 300), new Beta(bombs[5], level, 25, 200), new Beta(bombs[6], level, 425, 200), new Beta(bombs[7], level, 125, 100), new Beta(bombs[8], level, 325, 100), new Gamma(bombs[9], level, 225, 0) };
    }
    else if (level == 2 && phase == 2)
    { // heart
        numOfEnemies = 10;
        bombs = new Bomb *[numOfEnemies];
        for (int i = 0; i < numOfEnemies; i++)
        {
            bombs[i] = new Bomb(level);
        }
        enemies = new Enemy *[numOfEnemies]
        { new Alpha(bombs[0], level, 25, 275), new Alpha(bombs[1], level, 125, 325), new Alpha(bombs[2], level, 325, 325), new Alpha(bombs[3], level, 425, 275), new Beta(bombs[4], level, 75, 150), new Beta(bombs[5], level, 125, 50), new Beta(bombs[6], level, 375, 150), new Beta(bombs[7], level, 325, 50), new Gamma(bombs[8], level, 225, 0), new Gamma(bombs[9], level, 225, 275) };
    }
    else if (level == 2 && phase == 3)
    { // circle
        numOfEnemies = 12;
        bombs = new Bomb *[numOfEnemies];
        for (int i = 0; i < numOfEnemies; i++)
        {
            bombs[i] = new Bomb(level);
        }
        enemies = new Enemy *[numOfEnemies]
        { new Alpha(bombs[0], level, 90, 230), new Alpha(bombs[1], level, 150, 285), new Alpha(bombs[2], level, 225, 300), new Alpha(bombs[3], level, 300, 285), new Alpha(bombs[4], level, 360, 230), new Beta(bombs[5], level, 75, 150), new Beta(bombs[6], level, 90, 70), new Beta(bombs[7], level, 360, 70), new Beta(bombs[8], level, 375, 150), new Gamma(bombs[9], level, 140, 15), new Gamma(bombs[10], level, 225, 0), new Gamma(bombs[11], level, 305, 15) };
    }
    else if (level >= 3 && phase == 1)
    { // filled diamond
        numOfEnemies = 14;
        bombs = new Bomb *[numOfEnemies];
        for (int i = 0; i < numOfEnemies; i++)
        {
            bombs[i] = new Bomb(level);
        }
        enemies = new Enemy *[numOfEnemies]
        { new Alpha(bombs[0], level, 25, 300), new Alpha(bombs[1], level, 125, 300), new Alpha(bombs[2], level, 225, 300), new Alpha(bombs[3], level, 325, 300), new Alpha(bombs[4], level, 425, 300), new Beta(bombs[5], level, 25, 200), new Beta(bombs[6], level, 425, 200), new Beta(bombs[7], level, 125, 100), new Beta(bombs[8], level, 325, 100), new Gamma(bombs[9], level, 225, 0), new Alpha(bombs[10], level, 125, 200), new Alpha(bombs[11], level, 325, 200), new Alpha(bombs[12], level, 225, 100), new Beta(bombs[13], level, 225, 200) };
    }
    else if (level >= 3 && phase == 2)
    { // filled heart
        numOfEnemies = 15;
        bombs = new Bomb *[numOfEnemies];
        for (int i = 0; i < numOfEnemies; i++)
        {
            bombs[i] = new Bomb(level);
        }
        enemies = new Enemy *[numOfEnemies]
        { new Alpha(bombs[0], level, 25, 275), new Alpha(bombs[1], level, 125, 325), new Alpha(bombs[2], level, 325, 325), new Alpha(bombs[3], level, 425, 275), new Beta(bombs[4], level, 75, 150), new Beta(bombs[5], level, 125, 50), new Beta(bombs[6], level, 375, 150), new Beta(bombs[7], level, 325, 50), new Gamma(bombs[8], level, 225, 0), new Gamma(bombs[9], level, 225, 275), new Alpha(bombs[10], level, 125, 250), new Alpha(bombs[11], level, 325, 250), new Alpha(bombs[12], level, 225, 85), new Beta(bombs[13], level, 175, 165), new Beta(bombs[14], level, 275, 165) };
    }
    else if (level >= 3 && phase == 3)
    { // filled rectangle
        numOfEnemies = 15;
        bombs = new Bomb *[numOfEnemies];
        for (int i = 0; i < numOfEnemies; i++)
        {
            bombs[i] = new Bomb(level);
        }
        enemies = new Enemy *[numOfEnemies]
        { new Alpha(bombs[0], level, 25, 250), new Alpha(bombs[1], level, 125, 250), new Alpha(bombs[2], level, 225, 250), new Alpha(bombs[3], level, 325, 250), new Alpha(bombs[4], level, 425, 250), new Beta(bombs[5], level, 25, 150), new Beta(bombs[6], level, 25, 50), new Beta(bombs[7], level, 425, 150), new Beta(bombs[8], level, 425, 50), new Gamma(bombs[9], level, 125, 50), new Gamma(bombs[10], level, 225, 50), new Gamma(bombs[11], level, 325, 50), new Alpha(bombs[12], level, 125, 150), new Alpha(bombs[13], level, 325, 150), new Beta(bombs[14], level, 225, 150) };
    }
    else if (phase == 4)
    { // monster

        p->lives+=level;
        numOfEnemies = 1;
        enemies = new Enemy *[numOfEnemies]
        { new Monster(level, sizex / 2, 0) };
        bombs = new Bomb *[numOfEnemies];
        for (int i = 0; i < numOfEnemies; i++)
        {
            bombs[i] = new Bomb(level);
        }
    }
    enemiesBool = new bool[numOfEnemies];
    for (int i = 0; i < numOfEnemies; i++)
        enemiesBool[i] = true;
}

void Game::drawEnemiesAndPlayer(RenderWindow &window)
{
    if (draBool)
    {
        window.draw(dragon->sprite);
        if (dragon->bOnScreen)
            window.draw(dragon->b->sprite);
    }
    else
    {

        for (int i = 0; i < numOfEnemies; i++)
        {
            if (enemiesBool[i])
            {
                window.draw(enemies[i]->sprite);
                if (enemies[i]->bOnScreen)
                {
                    window.draw(enemies[i]->b->sprite);
                }
            }

            else if ((bombs[i]->y_pos < sizey))
            {
                window.draw(bombs[i]->sprite);
            }
            bombs[i]->move();
        }
    }
    if (addonNum != -1)
    {
        window.draw(addon[addonNum]->sprite);
    }
    static bool a = false;

    if (p->immortal)
    {
        if (a)
            window.draw(p->sprite);
        a = !a;
    }
    else
        window.draw(p->sprite);
}
void Game::enemyBomb(float time)
{
    for (int i = 0; i < numOfEnemies; i++)
    {
        if (enemiesBool[i])
            enemies[i]->bomb(time);
    }
}

void Game::collision()
{ // for invadors and player

    for (int i = 0; i < numOfEnemies; i++)
    {
        int temp = 0;
        if (enemiesBool[i])
        {
            if (p->addonbool)
            {
                if (p->addon->type == 4)
                {
                    for (int j = 0; j < 7; j++)
                    {
                        if (enemies[i]->collision(p->addon->bullets[j]->sprite))
                        {
                            score += enemies[i]->point();
                            delete enemies[i];
                            enemiesBool[i] = false;
                            p->addon->bullets[j]->y_pos = -100;
                            break;
                        }
                    }
                }
            }
            if (!enemiesBool[i])
                continue;
            bool tempA = enemies[i]->collision(p->sprite);
            bool tempB = enemies[i]->collision(p->b->sprite);
            if (tempA || tempB)
            {
                bombs[i]->x_pos = enemies[i]->b->x_pos, bombs[i]->y_pos = enemies[i]->b->y_pos;

                int addontemp = (level<5)? (rand() % (6-level)): 0; // level 1:20, 2:35, 3:33, 4:50 , 100% chance of an enemy giving any kind of addon
                if (addonNum == -1 && addontemp == 0)
                {
                    addonNum = rand() % 4;
                    addon[addonNum]->x_pos = enemies[i]->x_pos;
                    addon[addonNum]->y_pos = enemies[i]->y_pos;
                    addon[addonNum]->sprite.setPosition(addon[addonNum]->x_pos, addon[addonNum]->y_pos);
                }
                if (tempB)
                {
                    score += enemies[i]->point() * level;
                    if (!(p->addonbool))
                    {
                        p->b->x_pos = -50, p->b->y_pos = -50;
                        p->bOnScreen = false;
                    }
                    else if (p->addon->type != 1)
                    {
                        p->b->x_pos = -50, p->b->y_pos = -50;
                        p->bOnScreen = false;
                    }
                    delete enemies[i];
                    enemiesBool[i] = false;
                }
                else if (tempA && !p->immortal)
                {
                    p->x = 230;
                    p->y = 560;
                    p->immortal = true;
                    p->lives--;
                }
            }
            else if (enemies[i]->bOnScreen)
            {

                if (p->collision(enemies[i]->b->sprite) && !p->immortal)
                {
                    delete enemies[i]->b;
                    enemies[i]->bOnScreen = false;
                    p->x = 230;
                    p->y = 560;
                    p->immortal = true;
                    p->lives -= 1;
                }
            }

        }
        else if (p->collision((bombs[i]->sprite)) && !p->immortal)
        {
            bombs[i]->y_pos = 1111, bombs[i]->x_pos = 1000;
            p->lives -= 1;
            p->x = 230;
            p->y = 560;
            p->immortal = true;
            bombs[i]->sprite.setPosition(bombs[i]->x_pos, bombs[i]->y_pos);
        }
    }
}
bool Game::gameOver()
{
    if (p->lives > 0)
        return false;

    file.writeFile(name, score);
    return true;
}
void Game::gameOverUi(RenderWindow &window)
{
    Text text;
    text.setFillColor(Color::White);

    while (window.isOpen())
    {

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Enter)) // If down key is pressed
                return;
        }

        window.clear(Color::Black);
        window.draw(background);

        text.setFont(font);
        text.setStyle(Text::Bold);

        text.setCharacterSize(60);
        text.setString("Game Over");
        text.setPosition(100, 200);
        // Draw it
        window.draw(text);

        std::stringstream ss;
        ss << "Score: " << score;

        text.setCharacterSize(40);
        text.setString(ss.str());
        text.setPosition(170, 350);
        window.draw(text);

        text.setCharacterSize(25);
        text.setString("press enter to continue");
        text.setPosition(250, 600);
        window.draw(text);

        window.display();
    }
}

void Game::changeLevel(RenderWindow &window)
{

    if (phase == 4)
    {
        if (enemies[0]->timeComplete())
        {
            score += enemies[0]->point() * level;
            delete enemies[0];
            delete[] enemies;

            enemiesBool[0] = false;
        }
    }
    for (int i = 0; i < numOfEnemies; i++)
    {
        if (enemiesBool[i])
            return;
    }
    delete[] enemiesBool;
    for (int i = 0; i < numOfEnemies; i++)
        delete bombs[i];
    delete[] bombs;

    if (phase <= 3)
        phase++;
    else
    {
        phase = 1, level++;
        levelChangeAnimation(window);
    }

    makeEnemy();
}

void Game::addOnFunction(float time)
{
    if (addonNum != -1)
    {
        if (p->collision(addon[addonNum]->sprite) && !(p->addonbool))
        {
            switch (addon[addonNum]->type)
            {
            case 1:
                p->addon = new Fire();
                break;
            case 2:
                p->addon = new Lives();
                break;
            case 3:
                p->addon = new Danger();
                break;
            case 4:
                p->addon = new PowerUp;
                break;
            default:
                break;
            }
            *(p->addon) = *addon[addonNum];

            addonNum = -1;
            p->addonbool = true;
            p->addOnFunction();
        }
        else if (addon[addonNum]->y_pos > sizey)
        {
            if (addon[addonNum]->danger())
            {
                score += 5 * level;
            }
            addonNum = -1;
        }
        else
        {
            addon[addonNum]->move();
        }
    }
    if (p->addonbool)
    {
        p->addon->timer += time;

        if (p->addon->timer >= 5)
        {
            delete p->addon;
            p->addonbool = false;
        }
    }
}

void Game::showPoints(RenderWindow &window)
{

    Text text;
    text.setCharacterSize(35);
    text.setFont(font);
    text.setStyle(Text::Bold);
    text.setFillColor(Color::White);

    std::stringstream ss;
    ss << "Points: " << score << "\tlevel: " << level << "\tlives: " << p->lives << std::endl;

    text.setString(ss.str());
    text.setPosition(5, 5);
    window.draw(text);
}

void Game::levelChangeAnimation(RenderWindow &window)
{
    Bomb *b[2];
    Alpha a[] = {Alpha(b[0], 1, -70, 200), Alpha(b[1], 2, 550, 200)};
    while (window.isOpen())
    {

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);
        window.draw(background);

        if (a[0].collision(a[1].sprite))
        {
            sleep(milliseconds(100));
            return;
        }

        a[0].x_pos += 0.5, a[1].x_pos -= 0.5;
        a[0].sprite.move(0.5, 0), a[1].sprite.move(-0.5, 0);

        window.draw(a[0].sprite);
        window.draw(a[1].sprite);

        window.display();
    }
}

void Game::dragonFunctions(float time)
{

    dragon->x_pos = sizex / 2 - dragon->sprite.getGlobalBounds().width / 2;
    dragon->y_pos = 0;
    dragon->sprite.setPosition(dragon->x_pos, dragon->y_pos);

    dragon->bomb(time, 1 - (int)(p->x + p->sprite.getGlobalBounds().width / 2) / 175);

    if ((dragon->collision(p->sprite) || p->collision(dragon->sprite)) && !p->immortal)
    {
        p->x = 230;
        p->y = 560;
        p->immortal = true;
        p->lives--;
    }

    if (dragon->getTime() > 5 * level)
    {
        score += 50 * level;
        dragon->setTime(0);
        draBool = false;
        dragon->x_pos = 5000;
        dragon->y_pos = 5000;
        dragon->sprite.setPosition(dragon->x_pos, dragon->y_pos);
    }
}

Game:: ~Game(){

for(int i=0 ; i<numOfEnemies ; i++){
    if(enemiesBool[i])
        delete enemies[i];
    delete bombs[i];
}
delete[] enemies;
delete[] bombs;
for(int i=0 ;i<4 ; i++){
    delete addon[i];
}
delete[] addon;
delete bullet;
delete p;
delete dragon;

}