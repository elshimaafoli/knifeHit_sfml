#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace sf;
int main()
{

    RenderWindow window(sf::VideoMode(500, 800), "SFML works!");
    Texture target;
    Texture knifeTe;
    Texture apple;
Font font;
 font.loadFromFile("font/arial.ttf");
      Text gameover;
    gameover.setFillColor(Color::Blue);
    gameover.setString("GameOver");
    gameover.setCharacterSize(40);
    gameover.setPosition(100,200);
    gameover.setStyle(Text::Bold);
    gameover.setFont(font);

    int scoreNum=0;
     Text textNum;
    textNum.setFillColor(Color::Blue);
    textNum.setString(std::to_string(scoreNum));
    textNum.setCharacterSize(20);
    textNum.setPosition(60,0);
    textNum.setStyle(Text::Bold);
    textNum.setFont(font);
    int shootNum=-1;
    apple.loadFromFile("images/apple.png");
    CircleShape appleSp;
    appleSp.setTexture(&apple);
    appleSp.setRadius(20);

    RectangleShape knifeSp(Vector2f(100,100));
    float angle=0.1;

    target.loadFromFile("images/target.png");
    knifeTe.loadFromFile("images/knife-.png");
    knifeSp.setOrigin(knifeSp.getGlobalBounds().width/2,knifeSp.getGlobalBounds().height/2);
    knifeSp.setPosition(window.getSize().x/2,700);
    CircleShape shape(100.f);
    knifeSp.setTexture(&knifeTe);
    shape.setTexture(&target);
    Text score;
    score.setString("Score");
    score.setFont(font);
    double distance;
    int cx,cy;
    bool shoot=0;
    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)window.close();
            if(event.type==Event::KeyPressed){
                if(event.key.code==Keyboard::Space)
                    shoot=true;
            }
            }

        window.clear();
        cx=shape.getPosition().x;
        cy=shape.getPosition().y;
        shape.setOrigin(100,100);
        appleSp.setOrigin(100,100);
        shape.setPosition(window.getSize().x/2,window.getSize().y/3);
        appleSp.setPosition(cx,cy);
        appleSp.rotate(angle);
        shape.rotate(angle);
        if(shoot)knifeSp.move(0,shootNum);
        if(knifeSp.getPosition().x<=(window.getSize().x/2)+100&&knifeSp.getPosition().y<=(window.getSize().y/3)+100) {
                shootNum=0;
                angle=0;
                        if(){
                            scoreNum++;
                        } else {
                    window.draw(gameover);

                        }
        }
        window.draw(knifeSp);
        window.draw(shape);
        window.draw(score);
        window.draw(textNum);
        window.draw(appleSp);
        window.display();
    }

    return 0;
}
