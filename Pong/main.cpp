#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include <time.h>

#include "Game.h"

int main()
{
    srand(time(0));
    const int windowWidth = 1600;
    const int windowHeight = 900;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Arkanoid");

    sf::Event event;
    sf::Clock clock;
    Game game({ windowWidth, windowHeight });
    game.init();

    sf::View view(sf::FloatRect(0.f, 0.f, windowWidth, windowHeight));
    view.setCenter(windowWidth / 2.f, windowHeight / 2.f);
    view.zoom(0.5f);
    window.setView(view);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        float time = clock.restart().asSeconds();

        game.update(time);

        window.clear();
        game.render(window);
        window.display();
    }

    return 0;
}