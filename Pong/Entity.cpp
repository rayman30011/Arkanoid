#include "Entity.h"

void Entity::render(sf::RenderTarget& target)
{
	const auto position = _sprite->getPosition();
	int x = position.x;
	int y = position.y;
	_sprite->setPosition(static_cast<float>(x), static_cast<float>(y));
	target.draw(*_sprite);
	_sprite->setPosition(position);
}

void Entity::setPosition(sf::Vector2f position)
{
	_sprite->setPosition(position);
}
