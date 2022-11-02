#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
    RenderWindow window(sf::VideoMode(500, 800), "SFML works!");
    Texture target;
    Texture knifeTe;
    Font font;
    RectangleShape knifeSp(Vector2f(100,100));
    float angle=0.1;
    font.loadFromFile("font/arial.ttf");
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

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        shape.setOrigin(100,100);
        shape.setPosition(window.getSize().x/2,window.getSize().y/3);
        shape.rotate(angle);
        window.draw(shape);
        window.draw(score);
        window.draw(knifeSp);
        window.display();
    }

    return 0;
}
