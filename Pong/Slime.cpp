#include "Slime.h"
#include "utils.hpp"

Slime::Slime(Game* game): Entity(game)
{
	if (!_image->loadFromFile("resources/slime.png"))
		throw;
	_texture->loadFromImage(*_image);
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(sf::IntRect(0, 0, 16, 16));

	_speed = 0.01f;
}

void Slime::start()
{
	retarget();
}

void Slime::update(float deltaTime)
{
	const auto currentPosition = _sprite->getPosition();
	auto direction = _target - currentPosition;
	if (len(direction) <= 3.5f)
	{
		retarget();
	}
	normilize(direction);
	auto step = direction * _speed;
	_sprite->move(step);
}

void Slime::retarget()
{
	const auto windowRec = _game->getMapRect();
	int x = rand() % windowRec.width;
	int y = rand() % windowRec.height;
	_target.x = x + windowRec.left;
	_target.y = y + windowRec.top;
}
