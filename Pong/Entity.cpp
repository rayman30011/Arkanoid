#include "Entity.h"

void Entity::render(sf::RenderTarget& target)
{
	target.draw(_sprite);
}
