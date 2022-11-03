#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<bits/stdc++.h>
using namespace sf;

int main()
{

    RenderWindow window(sf::VideoMode(500, 800), "Knife Hit");
    //window.setFramerateLimit(30);
    RectangleShape knifeSpRec[3];

    float angle=0.05;
    int shootSpeed=-1,knives_num=3, speedLevel=1;
    int cx,cy, spY=-70;
    bool shoot=0, applecheck=0,inside=1,newGame=0;

    Font font;
    if(!font.loadFromFile("font/arial.ttf"))return -1;

    SoundBuffer bkBuffer,shootBuffer,vanishBuffer;
    Sound bkSound, shootSound,vanishSound;
    if(!bkBuffer.loadFromFile("sounds/bg.wav")) return -1;

    bkSound.setBuffer(bkBuffer);
    bkSound.play();
    bkSound.setLoop(true);
    bkSound.setVolume(30);

    if(!vanishBuffer.loadFromFile("sounds/cut-audio.wav"))return -1;
    vanishSound.setBuffer(vanishBuffer);

    if(!shootBuffer.loadFromFile("sounds/shoot.wav"))return -1;
    shootSound.setBuffer(shootBuffer);

    Texture bkground, targetTex, knifeTe, apple,knifeSpTex;

    if(!knifeSpTex.loadFromFile("images/knife-spare.png"))return -1;

    if(!bkground.loadFromFile("images/bkground.jpg"))return -1;
    RectangleShape bkgroundimg(Vector2f(500,800));
    bkgroundimg.setTexture(&bkground);

    Text gameover;
    gameover.setFillColor(Color::Blue);
    gameover.setString("GameOver");
    gameover.setCharacterSize(40);
    gameover.setOrigin(gameover.getGlobalBounds().width/2,gameover.getGlobalBounds().height/2);
    gameover.setPosition(window.getSize().x/2,window.getSize().y/2);
    gameover.setStyle(Text::Bold);
    gameover.setFont(font);

    int scoreNum=0;
    Text textNum;
    textNum.setFillColor(Color::White);
    textNum.setString(std::to_string(scoreNum));
    textNum.setCharacterSize(30);
    textNum.setPosition(80,0);
    textNum.setFont(font);

    Text speedText;
    speedText.setFillColor(Color::White);
    speedText.setString("Speed");
    speedText.setCharacterSize(20);
    speedText.setOrigin(speedText.getGlobalBounds().width/2,speedText.getGlobalBounds().height/2);
    speedText.setPosition(400,0);
    speedText.setFont(font);

    Text speedLevelTex;
    speedLevelTex.setFillColor(Color::White);
    speedLevelTex.setString(std::to_string(speedLevel));
    speedLevelTex.setCharacterSize(20);
    speedLevelTex.setPosition(470,0);
    speedLevelTex.setFont(font);

    if(!apple.loadFromFile("images/apple.png")) return -1;
    CircleShape appleSp;
    appleSp.setTexture(&apple);
    appleSp.setRadius(20);
    appleSp.setOrigin(100,100);

    CircleShape appleScore;
    appleScore.setTexture(&apple);
    appleScore.setRadius(20);
    appleScore.setPosition(20,0);


    RectangleShape knife(Vector2f(100,100));
    if(!knifeTe.loadFromFile("images/knife-.png")) return -1;
    knife.setOrigin(knife.getGlobalBounds().width/2,knife.getGlobalBounds().height/2);
    knife.setPosition(window.getSize().x/2,700);
    knife.setTexture(&knifeTe);

    if(!targetTex.loadFromFile("images/target.png"))return -1;
    CircleShape target(100.f);
    target.setTexture(&targetTex);
    target.setOrigin(100,100);
    target.setPosition(window.getSize().x/2,window.getSize().y/3);


    for(int i = 0; i<3; i++)
    {
        knifeSpRec[i].setSize(Vector2f(50.f,50.f));
        knifeSpRec[i].setTexture(&knifeSpTex);
        knifeSpRec[i].setPosition(20,window.getSize().y+spY);
        spY-=70;
    }

    while (window.isOpen())
    {


        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)window.close();

            if(event.type==Event::KeyPressed)
            {
                if(event.key.code==Keyboard::Space)
                {
                    shoot=true;
                    inside=1;

                    shootSpeed=-1;
                    shootSound.play();

                }
            }
        }

        window.clear();
        window.draw(bkgroundimg);
        cx=target.getPosition().x;
        cy=target.getPosition().y;
        appleSp.setPosition(cx,cy);

        appleSp.rotate(angle);
        target.rotate(angle);


        if(shoot)
            knife.move(0,shootSpeed);


        if(shoot&&knife.getPosition().x<=(window.getSize().x/2)+100&&knife.getPosition().y<=(window.getSize().y/3)+100)
        {
            // win .. striking the apple
            if(inside&&appleSp.getGlobalBounds().contains(knife.getPosition().x,knife.getPosition().y))
            {
                scoreNum++;
                inside=0;
                //applecheck=1;
                speedLevel++;
                angle+=0.1;
                shootSpeed=0;
                knife.setPosition(window.getSize().x/2,700);
                //  shoot=0;
                newGame=1;
                vanishSound.play();
            }
            // lose
            else if(inside)
            {
                if(knives_num<=1)
                {
                    knives_num--;
                    shootSpeed=0;
                    angle=0;
                    window.draw(gameover);
                    bkSound.stop();
                }
                //strike the wood
                else
                {
                    knives_num--;
                    std::cout<<knives_num<<std::endl;
                    shoot=0;
                    applecheck=0;
                    knife.setPosition(window.getSize().x/2,700);
                    shootSpeed=0;
                    //angle=0;

                }
            }

        }
        window.draw(knife);
        window.draw(target);
        window.draw(speedText);
        speedLevelTex.setString(std::to_string(speedLevel));
        window.draw(speedLevelTex);
        window.draw(appleScore);
        textNum.setString(std::to_string(scoreNum));
        window.draw(textNum);
        for(int i=0; i<knives_num; i++)
        {
            window.draw(knifeSpRec[i]);
        }
        if(!applecheck)window.draw(appleSp);
        window.display();
    }

    return 0;
}
