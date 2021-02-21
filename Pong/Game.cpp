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
            Bonus* bonus = createEntity<Bonus>();
            bonus->setType(Bonus::Type::Double);
            bonus->setPosition(params.position);
    	}
    });

    _bgTexture.loadFromFile("resources/back.png");
    _bgSprite.setTexture(_bgTexture);

    reinitMap();
	restart();

    Slime* slime = createEntity<Slime>();
    slime->setPosition({ 800, 450 });

    slime = createEntity<Slime>();
    slime->setPosition({ 860, 400 });
}

void Game::update(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && _isBallFollow) 
    {
		_isBallFollow = false;
	}

    const auto position = _ball->getPosition();
    const auto speed = _ball->getSpeed();
    auto direction = _ball->getDirection();
    
    const float next_y = position.y + direction.y * time * speed;
    const float next_x = position.x + direction.x * time * speed;

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
    isCollide(*_ball, constants::Layer::Enemy);
    isCollide(*_player, constants::Layer::Bonus);

	for (auto it = _entities.begin(); it != _entities.end();)
	{
        (*it)->update(time);
        if ((*it)->isDestroyed())
        {
            it = _entities.erase(it);
            continue;
        }

        ++it;
	}
}

void Game::render(sf::RenderTarget& target)
{
    _bgSprite.setPosition(sf::Vector2f(_mapRect.left, _mapRect.top));
    target.draw(_bgSprite);
    _mapRenderer->render(target);
	_ball->render(target);

    for (Entity* entity : _entities) {
        entity->render(target);
    }
    
    target.draw(_scoreText);
}

bool Game::isCollide(Entity& entity, constants::Layer layer = constants::Layer::Undefined)
{
	if (!entity.isCollidable())
	{
        return false;
	}
	
    auto mask = layer;
	if (layer == constants::Layer::Undefined)
	{
        mask = entity.getLayer();
	}
	
	for (auto* el: _entities)
	{
		if (el->getLayer() == mask && el->isCollidable())
		{
            auto mainEntityRect = entity.getBoundRect();
            auto otherEntityRect = el->getBoundRect();
			if (mainEntityRect.intersects(otherEntityRect))
			{
                entity.onCollide(*el);
                el->onCollide(entity);
                return true;
			}
		}
	}
	
    return false;
}

std::vector<Entity*> Game::getEntitiesByName(std::string name)
{
    std::vector<Entity*> result;
    for (auto entity : _entities)
    {
	    if (entity->getName() == name)
	    {
            result.push_back(entity);
	    }
    }
    return result;
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
