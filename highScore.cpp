#include "highScore.h"
#include <string.h>
using namespace std;

highScore::highScore (std:: string str){
    bg_texture.loadFromFile("img/background.png");
    background.setTexture(bg_texture);
    background.setScale(1.5, 1);
    font.loadFromFile("font/Carpet.ttf");
    fileName = str;

    b1.loadFromFile("img/star_gold.png");
    b2.loadFromFile("img/star_silver.png");
    b3.loadFromFile("img/star_bronze.png");

    badge1.setTexture(b1);
    badge2.setTexture(b2);
    badge3.setTexture(b3);

}

    void highScore::displayHighScore(RenderWindow& window)
    {

        window.clear(Color::Black);
        readFile();
        Texture obj;
        obj.loadFromFile("img/buttonRed.png");
        Sprite button(obj);

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

                        if ((x_pos > 150 && x_pos < (150 + 229)) && (y_pos > 550 && y_pos < (550 + 39))){
                            return;
                        }
                    }
                }
            }
            std::stringstream ss;
            ss << "No.             Name          Score\n";

            for (int i = 0; i < 10; i++)
            {
                if(i>2){
                    ss << (i + 1)<< ". ";
                }
                else
                    ss<<"   ";
                ss << std::setw(20) << name[i] << std::setw(20) << score[i] << std::endl;
            }

            window.draw(background);
            Text text;
            text.setFont(font);
            text.setCharacterSize(35);
            text.setStyle(Text::Bold);
            text.setFillColor(Color::White);

            text.setString(ss.str());
            text.setPosition(50, 10);
            window.draw(text);

            button.setPosition(150,550);
            button.setColor(Color::Black);
            window.draw(button);

            
            badge1.setPosition(50,55);
            window.draw(badge1);
            badge2.setPosition(50,105);
            window.draw(badge2);
            badge3.setPosition(50,155);
            window.draw(badge3);
            // text.setFillColor(Color:: Black);
            
            text.setString("Back");
            text.setPosition(220,545);
            window.draw(text);
            
            window.display();
        }
    }
void highScore:: readFile(){
	ifstream infile(fileName);
	int index=0;

 	while(!infile.eof() && index<10){
        int i= 0; char* c = new char[20];
        while(infile.get(c[i])){
            if(c[i] == ',')
                break;
            i++;
        }
        c[i] = '\0';
        name[index] = c;
        infile>>score[index];
        infile.get(c[i]);
        index++;
	}
    infile.close();    
}

void highScore:: writeFile(string n, int sco)
{
	fstream infile(fileName, ios::in);
    stringstream ss;
    bool done = false;
    string namestemp;
    int scorestemp;

 	while(!infile.eof())
    {
        int i= 0; char* c = new char[20];
        while(infile.get(c[i])){
            if(c[i] == ',')
                break;
            i++;
        }
        c[i] = '\0';
        namestemp = c;
        infile>>scorestemp;
        infile.get(c[i]);

        if(sco>=scorestemp && !done){
            ss << n << ',' << sco<< endl;
            ss << namestemp << ',' << scorestemp <<endl;
            done = true; 
        }
        else{
            ss << namestemp << ',' << scorestemp<< endl;
        }
	}
    if(!done){
        ss << n << ',' << sco<<endl;
    }
    infile.close(); 
	fstream file(fileName, ios::out);

    file<< ss.str();
    file.close();
}

std::string highScore:: getName(int i){
    if(i>=0 && i<10)
        return name[i];
    return "";
}
int highScore:: getScore(int i){
    if(i>=0 && i<10)
        return score[i];
    return -1;    
}