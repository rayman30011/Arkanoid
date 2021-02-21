#include "Bonus.h"


#include <iostream>
#include <SFML/Graphics.hpp>

#include "Ball.h"

Bonus::Bonus(Game* game): Entity(game)
{
	_image = std::make_unique<sf::Image>();
	_image->loadFromFile("resources/bonus.png");

	_texture = std::make_unique<sf::Texture>();
	_texture->loadFromImage(*_image);

	_sprite = std::make_unique<sf::Sprite>();
	_sprite->setTexture(*_texture);
	_sprite->setOrigin(8, 8);
	_sprite->setTextureRect(sf::IntRect(static_cast<int>(_type) * 16, 0, 16, 16));
}

void Bonus::start()
{
	setCollidable(true);
	setLayer(constants::Layer::Bonus);
}

void Bonus::update(float dt)
{
	_sprite->move({ 0, 100 * dt });
}

void Bonus::onCollide(Entity& other)
{
	if (other.getName() != "player")
	{
		return;
	}
	
	switch (_type)
	{
	case Type::Double:
		doubleBall();
		break;
	case Type::None: break;
	case Type::SpeedUp: break;
	case Type::SpeedDown: break;
	case Type::SizeUp: break;
	case Type::SizeDown: break;
	default: ;
	}
	destroy();
}

void Bonus::doubleBall()
{
	auto balls = getGame()->getEntitiesByName("ball");
	for (auto* ball : balls)
	{
		auto casted = static_cast<Ball*>(ball);
		auto* newBall = getGame()->createEntity<Ball>();
		newBall->setPosition(ball->getPosition());
		auto ballDirection = casted->getDirection();
		ballDirection.x = -ballDirection.x;
		newBall->set_direction(ballDirection);
	}
}
