#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Pong");

    sf::Event event;
    sf::Image deck;
    deck.loadFromFile("resources/deck.png");
    sf::Texture texture;
    texture.loadFromImage(deck);
    texture.setSmooth(false);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    Entity entity;
    
    entity.setSprite(sprite);
    entity.setPosition({ 50, 100 });

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            window.clear(sf::Color::Blue);

            entity.render(window);

            window.display();
        }
    }

    return 0;
}