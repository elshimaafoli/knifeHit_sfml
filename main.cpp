#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        shape.setOrigin(shape.getGlobalBounds().width/2,shape.getGlobalBounds().height/2);
        shape.setPosition(window.getSize().x/2,window.getSize().y/3);
        window.draw(shape);
        window.display();
    }

    return 0;
}
