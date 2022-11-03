#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<bits/stdc++.h>
using namespace sf;

int main()
{

    RenderWindow window(sf::VideoMode(500, 800), "Knife Hit");
    //window.setFramerateLimit(30);

    //Defining our variables
    RectangleShape knife(Vector2f(100,100)), bgGroundImg(Vector2f(500,800)),knifeSpRec[3];
    CircleShape appleSp, appleScore, target(100.f);
    Texture bgGround, targetTex, knifeTe, appleTex,knifeSpTex;

    float angle=0.05;
    int shootSpeed=-1,knives_num=3, speedLevel=1;
    int cx,cy, win_x,win_y,spY=-70;
    bool shoot=0, applecheck=0,inside=1, over = 0;

    win_x = window.getSize().x;
    win_y = window.getSize().y;

    Font font;
    if(!font.loadFromFile("font/arial.ttf"))return -1;

    //Initializing and loading sounds
    SoundBuffer bgBuffer,shootBuffer,vanishBuffer;
    Sound bgSound, shootSound,vanishSound;
    if(!bgBuffer.loadFromFile("sounds/bg.wav")) return -1;
    bgSound.setBuffer(bgBuffer);

    if(!vanishBuffer.loadFromFile("sounds/cut-audio.wav"))return -1;
    vanishSound.setBuffer(vanishBuffer);

    if(!shootBuffer.loadFromFile("sounds/shoot.wav"))return -1;
    shootSound.setBuffer(shootBuffer);

    // Playing sound in the background
    bgSound.play();
    bgSound.setLoop(true);
    bgSound.setVolume(30);

    //Loading and configuring images
    if(!knifeTe.loadFromFile("images/knife.png")) return -1;
    knife.setTexture(&knifeTe);
    knife.setOrigin(knife.getGlobalBounds().width/2,knife.getGlobalBounds().height/2);
    knife.setPosition(win_x/2,700);

    if(!appleTex.loadFromFile("images/apple.png")) return -1;
    appleSp.setTexture(&appleTex);
    appleSp.setRadius(20);
    appleSp.setOrigin(100,100);

    if(!targetTex.loadFromFile("images/target.png"))return -1;
    target.setTexture(&targetTex);
    target.setOrigin(100,100);
    target.setPosition(win_x/2,win_y/3);

    if(!knifeSpTex.loadFromFile("images/knife-spare.png"))return -1;

    if(!bgGround.loadFromFile("images/background.jpg"))return -1;
    bgGroundImg.setTexture(&bgGround);


    //Setting text
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

    Text gameover;
    gameover.setFillColor(Color::White);
    gameover.setString("Game Over");
    gameover.setCharacterSize(40);
    gameover.setPosition(win_x/2,win_y/2);
    gameover.setOrigin(40*9 - win_x/2,gameover.getGlobalBounds().height/2);
    gameover.setStyle(Text::Bold);
    gameover.setFont(font);

    Text overScore;
    overScore.setFillColor(Color::White);
    overScore.setCharacterSize(40);
    overScore.setPosition(win_x/2, win_y/2);
    overScore.setOrigin(0,overScore.getGlobalBounds().height/2 -50);
    overScore.setStyle(Text::Bold);
    overScore.setFont(font);

    appleScore.setTexture(&appleTex);
    appleScore.setRadius(20);
    appleScore.setPosition(20,0);

    //Specifying the spare knives
    for(int i = 0; i<3; i++)
    {
        knifeSpRec[i].setSize(Vector2f(50.f,50.f));
        knifeSpRec[i].setTexture(&knifeSpTex);
        knifeSpRec[i].setPosition(20,win_y+spY);
        spY-=70;
    }

    /*Game Loop*/
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

        /*-Game Logic*/
        window.draw(bgGroundImg);

        cx=target.getPosition().x;
        cy=target.getPosition().y;
        appleSp.setPosition(cx,cy);

        appleSp.rotate(angle);
        target.rotate(angle);


        if(shoot)
            knife.move(0,shootSpeed);


        if(shoot&&knife.getPosition().x<=(win_x/2)+100&&knife.getPosition().y<=(win_y/3)+100)
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
                knife.setPosition(win_x/2,700);
                //  shoot=0;

                //vanishSound.play();
            }
            // lose
            else if(inside)
            {
                over=0;
                if(knives_num<=1)
                {
                    knives_num--;
                    shootSpeed=0;
                    angle=0;
                    window.draw(gameover);
                    over = 1;
                    bgSound.stop();
                }
                //strike the wood
                else
                {
                    knives_num--;
                    std::cout<<knives_num<<std::endl;
                    shoot=0;
                    applecheck=0;
                    knife.setPosition(win_x/2,700);
                    shootSpeed=0;
                    //angle=0;
                }
            }
        }

        if(!over)
        {
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
        }else{
            overScore.setString(std::to_string(scoreNum));
            window.draw(overScore);
        }
        window.display();
    }

    return 0;
}
