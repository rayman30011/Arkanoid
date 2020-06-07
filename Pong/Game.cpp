#include "Game.h"
#include "utils.hpp"

#include <iostream>

Game::Game(sf::Vector2u windowSize)
{
	_windowSize = windowSize;
    _score = 0;
    _font = new sf::Font();
}

void Game::init()
{
	_ball = std::make_unique<Ball>("resources/ball.png");
	_player = std::make_unique<Player>("resources/deck.png");

	_currentMap = new Map("resources/levels/1.txt");
	_mapRenderer = new MapRenderer(_currentMap);

    _font->loadFromFile("resources/fonts/nullp.ttf");
    sf::Texture& texture = const_cast<sf::Texture&>(_font->getTexture(24));
    texture.setSmooth(false);
    
    _scoreText.setFont(*_font);
    _scoreText.setString("Score: " + std::to_string(_score));
    _scoreText.setCharacterSize(24);
    
    _scoreText.setPosition({ 10, 10 });
    _scoreText.setFillColor(sf::Color::Green);

    _currentMap->onBlockDestroy([this]() -> void {
        _score += 100;
        _scoreText.setString("Score: " + std::to_string(_score));
    });

	restart();
}

void Game::update(float time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && _isBallFollow) {
		_isBallFollow = false;
	}

    auto position = _ball->get_position();
    auto speed = _ball->get_speed();
    auto dir = _ball->get_direction();
    
    float next_y = position.y + dir.y * time * speed;
    float next_x = position.x + dir.x * time * speed;

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
    _ball->update(time);
    _player->update(time);
}

void Game::render(sf::RenderTarget& target)
{
	_ball->draw(target);
	_mapRenderer->render(target);
    _player->render(target);

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
