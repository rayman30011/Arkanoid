#include "Game.h"
#include "utils.hpp"
#include "Time.h"

#include <iostream>

Game::Game(sf::Vector2u windowSize)
{
	_windowSize = windowSize;
    _score = 0;
    _font = new sf::Font();
}

void Game::init()
{
	_ball = new Ball("resources/ball.png");
	_player = new Player("resources/deck.png");
    _entities.push_back(_player);
    _entities.push_back(_ball);

	_currentMap = new Map("resources/levels/1.txt");
	_mapRenderer = new MapRenderer(_currentMap);

    _font->loadFromFile("resources/fonts/PressStart.ttf");
    sf::Texture& texture = const_cast<sf::Texture&>(_font->getTexture(24));
    texture.setSmooth(false);
    
    _scoreText.setFont(*_font);
    _scoreText.setString("Score " + std::to_string(_score));
    _scoreText.setCharacterSize(18);
    
    _scoreText.setPosition({ 10, 10 });
    _scoreText.setFillColor(sf::Color::White);

    _currentMap->onBlockDestroy([this](BlockActionParams params) -> void
    {
        _score += 100;
        _scoreText.setString("Score " + std::to_string(_score));
    });

    _currentMap->onBlockDestroy([this](BlockActionParams params) -> void
    {
        int i = rand() % 5;
    	if (i <= 1)
    	{
            std::cout << "Bonus X:" << params.position.x << "\tY: " << params.position.y << std::endl;            auto bonus = new Bonus(Bonus::Type::Double);
            bonus->setPosition(params.position);
            _entities.push_back(bonus);
    	}
    });

	restart();
}

void Game::update(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && _isBallFollow) 
    {
		_isBallFollow = false;
	}

    const auto position = _ball->get_position();
    const auto speed = _ball->get_speed();
    auto dir = _ball->get_direction();
    
    const float next_y = position.y + dir.y * time * speed;
    const float next_x = position.x + dir.x * time * speed;

    if (next_y <= 0 || next_y >= _windowSize.y)
        dir.y = -dir.y;

    if (next_x <= 0 || next_x >= _windowSize.x)
        dir.x = -dir.x;

    auto rect = _ball->getBoundRect();
    rect.left = next_x;
    if (_currentMap->is_collide_block(rect))
    {
        dir.x = -dir.x;
        _currentMap->collide_block(rect);
        rect.left = position.x;
    }

    rect.top = next_y;
    if (_currentMap->is_collide_block(rect))
    {
        dir.y = -dir.y;
        _currentMap->collide_block(rect);
    }

    if (_player->getBoundRect().intersects(_ball->getBoundRect()))
        dir.y = -dir.y;

    _ball->set_direction(dir);

    for (auto& entity : _entities) {
        entity->update(time);
    }
}

void Game::render(sf::RenderTarget& target)
{
    _mapRenderer->render(target);
	_ball->render(target);

    for (auto& entity : _entities) {
        entity->render(target);
    }

    target.draw(_scoreText);
}

void Game::restart()
{
	_isBallFollow = true;
	
	auto deckSize = _player->getBoundRect();
	auto deckPosition = sf::Vector2f(_windowSize.x / 2 - deckSize.width / 2, _windowSize.y - 50);
    _player->setPosition(deckPosition);

	_ball->set_position(deckPosition + sf::Vector2f(0, 15));
	auto direction = sf::Vector2f(1, -1);
	normilize(direction);
	_ball->set_direction(direction);

	_currentState = State::Running;
}
