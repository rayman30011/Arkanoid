#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include <iostream>
#include <fstream>

#include "Ball.hpp"
#include "MapRenderer.h"

#include "Game.h"

int main()
{
    const int windowWidth = 600;
    const int windowHeight = 568;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Arkanoid");

    sf::Event event;
    sf::Clock clock;
    Game game({ windowWidth, windowHeight });
    game.init();

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        float time = clock.restart().asSeconds();

        game.update(time);

        window.clear(sf::Color(17, 54, 48));
        game.render(window);
        window.display();
    }

    return 0;
}