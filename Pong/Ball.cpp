#include "Ball.h"

void Ball::update(float deltaTime)
{
	sf::IntRect mapRect = getGame()->getMapRect();
	sf::Vector2f position = getPosition();

	const float nextY = position.y + _direction.y * deltaTime * _speed;
	const float nextX = position.x + _direction.x * deltaTime * _speed;
	
	if (nextX <= mapRect.left || nextX >= mapRect.left + mapRect.width)
	{
		_direction.x = -_direction.x;
	}

	if (nextY <= mapRect.top || nextY >= mapRect.top + mapRect.height)
	{
		_direction.y = -_direction.y;
		if (nextY >= mapRect.top + mapRect.height)
		{
			destroy();
		}
	}
	
	_sprite->move(_direction * _speed * deltaTime);
}
