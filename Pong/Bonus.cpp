#include "Bonus.h"

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
	switch (_type)
	{
	case Type::Double:
		doubleBall();
		{
			auto ball = getGame()->createEntity<Ball>();
			ball->setPosition({800.f, 350.f});
			ball->set_direction({ 1, 1 });
		}
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
	auto* const game = getGame();
	auto balls = game->getEntitiesByName("ball");
	for (auto* ball : balls)
	{
		auto* castedBall = static_cast<Ball*>(ball);
		auto newBall = game->createEntity<Ball>();
		auto oldDirection = castedBall->getDirection();
		newBall->set_direction({ -oldDirection.x, oldDirection.y });
		newBall->setPosition(castedBall->getPosition());
	}
}
