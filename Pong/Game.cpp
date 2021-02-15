#include "Game.h"
#include "utils.hpp"
#include "Time.h"
#include "Bonus.h"
#include "Player.h"

#include <iostream>
#include <Windows.h>

#include "Ball.h"
#include "Slime.h"

Game::Game(sf::Vector2u windowSize)
{
	_windowSize = windowSize;
    _score = 0;
    _font = new sf::Font();
}

void Game::init()
{
	_ball = new Ball(this);
	_player = new Player(this);
    _entities.push_back(_player);
    _entities.push_back(_ball);

	_currentMap = new Map("resources/levels/1.txt");

    lives = 3;
	
	_mapRenderer = new MapRenderer(_currentMap);

    _font->loadFromFile("resources/fonts/PressStart.ttf");
    sf::Texture& texture = const_cast<sf::Texture&>(_font->getTexture(24));
    texture.setSmooth(false);

    if (!_crtShader.loadFromFile("resources/crt.frag", sf::Shader::Fragment))
    {
        MessageBox(nullptr, TEXT("Error from compilation shader"), TEXT("EROOR"), 0);
        throw;
    }
	
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
        int i = rand() % 20;
    	if (i <= 2)
    	{
    		std::cout << "Bonus X:" << params.position.x << "\tY: " << params.position.y << std::endl;
    		Bonus* bonus = new Bonus(this);
            bonus->setType(Bonus::Type::Double);
            bonus->setPosition(params.position);
            _entities.push_back(bonus);
    	}
    });

    _bgTexture.loadFromFile("resources/back.png");
    _bgSprite.setTexture(_bgTexture);

    reinitMap();
	restart();

    Slime* slime = new Slime(this);
    slime->setPosition({ 800, 450 });
    slime->start();
    _entities.push_back(slime);
}

void Game::update(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && _isBallFollow) 
    {
		_isBallFollow = false;
	}

    const auto position = _ball->get_position();
    const auto speed = _ball->getSpeed();
    auto direction = _ball->getDirection();
    
    const float next_y = position.y + direction.y * time * speed;
    const float next_x = position.x + direction.x * time * speed;

    if (next_y <= _mapRect.top || next_y >= _mapRect.top + _mapRect.height)
    {
        direction.y = -direction.y;
    	if (next_y >= _mapRect.top + _mapRect.height)
    	{
            reinitMap();
            restart();
    	}
    }
        

    if (next_x <= _mapRect.left || next_x >= _mapRect.left + _mapRect.width)
        direction.x = -direction.x;

    auto rect = _ball->getBoundRect();
    rect.left = next_x;
    if (_currentMap->is_collide_block(rect))
    {
        direction.x = -direction.x;
        _currentMap->collide_block(rect);
        rect.left = position.x;
    }

    rect.top = next_y;
    if (_currentMap->is_collide_block(rect))
    {
        direction.y = -direction.y;
        _currentMap->collide_block(rect);
    }

    if (_player->getBoundRect().intersects(rect))
    {
        direction.y = -direction.y;
        const auto playerRect = _player->getBoundRect();
        auto tmp = rect;
        const auto left = playerRect.left;
        tmp.left -= left;
        direction.x = tmp.left / playerRect.width * 2 - 1;
    }

    normilize(direction);
    _ball->set_direction(direction);

    for (Entity* entity : _entities) 
    {
        entity->update(time);
    }
}

void Game::render(sf::RenderTarget& target)
{
    //sf::Shader::bind(&_crtShader);

    _bgSprite.setPosition(sf::Vector2f(_mapRect.left, _mapRect.top));
    target.draw(_bgSprite);
    _mapRenderer->render(target);
	_ball->render(target);

    for (Entity* entity : _entities) {
        entity->render(target);
    }
    
    target.draw(_scoreText);
	
    //sf::Shader::bind(nullptr);
}

bool Game::isCollide(const Entity& entity, constants::Layer layer = constants::Layer::Undefined)
{
    auto mask = layer;
	if (layer == constants::Layer::Undefined)
	{
        mask = entity.getLayer();
	}
	
	for (auto* el: _entities)
	{
		if (el->getLayer() == mask && entity.isCollidable())
		{
            auto mainEntityRect = entity.isCollidable();
		}
	}
	
    return false;
}

void Game::restart()
{
	_isBallFollow = true;
	
	const auto deckSize = _player->getBoundRect();
	const auto deckPosition = sf::Vector2f(_windowSize.x / 2 - deckSize.width / 2, _windowSize.y / 2 + 150);
    _player->setPosition(deckPosition);

	_ball->setPosition(deckPosition + sf::Vector2f(0, -55));
	auto direction = sf::Vector2f(1, -1);
	normilize(direction);
	_ball->set_direction(direction);

	_currentState = State::Running;
}

void Game::reinitMap()
{
    _currentMap->loadMap();
    const auto mapHeightInPixels = MAP_HEIDHT * BLOCK_WIDTH;
    const auto mapWidthInPixels = MAP_WIDTH * BLOCK_WIDTH;
    const auto yOffset = (_windowSize.y - mapHeightInPixels) / 2;
    const auto xOffset = (_windowSize.x - mapWidthInPixels) / 2;

    _mapRect.left = xOffset;
    _mapRect.width = mapWidthInPixels;
    _mapRect.top = yOffset;
    _mapRect.height = mapHeightInPixels;

    for (Block& block : _currentMap->getBlocks())
    {
        block.rect.left += xOffset;
        block.rect.top += yOffset;
    }
}
