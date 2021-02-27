#include "Ball.h"
#include "Player.h"
#include "utils.hpp"

void Ball::update(float deltaTime)
{
	sf::IntRect mapRect = getGame()->getMapRect();
	sf::Vector2f position = getPosition();

	const float nextY = position.y + _direction.y * deltaTime * _speed;
	const float nextX = position.x + _direction.x * deltaTime * _speed;
	const auto boundRect = getBoundRect();
	
	if (nextX <= mapRect.left || nextX + boundRect.width >= mapRect.left + mapRect.width)
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

	auto entities = getGame()->getEntitiesByName("player");
	auto* player = reinterpret_cast<Player*>(entities[0]);
	auto playerRect = player->getBoundRect();
	
	if (player->getBoundRect().intersects(boundRect))
	{
		_direction.y = -_direction.y;
		auto tmp = boundRect;
		const auto left = playerRect.left;
		tmp.left -= left;
		_direction.x = tmp.left / playerRect.width * 2 - 1;
	}


	auto* map = getGame()->getMap();
	auto tmpRect = boundRect;
	tmpRect.left = nextX;
	if (map->is_collide_block(tmpRect))
	{
		_direction.x = -_direction.x;
		map->collide_block(tmpRect);
		tmpRect.left = position.x;
	}

	tmpRect.top = nextY;
	if (map->is_collide_block(tmpRect))
	{
		_direction.y = -_direction.y;
		map->collide_block(tmpRect);
	}

	utils::normalize(_direction);
	_sprite->move(_direction * _speed * deltaTime);
}
