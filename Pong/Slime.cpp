#include "Slime.h"

Slime::Slime(Game* game): Entity(game)
{
	if (!_image->loadFromFile("resources/slime.png"))
		throw;
	_texture->loadFromImage(*_image);
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void Slime::start()
{
	
}

void Slime::render(sf::RenderTarget& target)
{
	target.draw(*_sprite);
}

void Slime::update(float deltaTime)
{
}
