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

sf::FloatRect Entity::getBoundRect() const
{
	sf::FloatRect resultRect;
	const auto position = getPosition();
	resultRect.left = position.x;
	resultRect.top = position.y;

	const auto& textureRect = _sprite->getTextureRect();
	resultRect.width = textureRect.width;
	resultRect.height = textureRect.height;
	
	return resultRect;
}

void Entity::destroy()
{
	_isDestroyed = true;
}
