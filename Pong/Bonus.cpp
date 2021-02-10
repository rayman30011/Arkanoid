#include "Bonus.h"

#include <SFML/Graphics.hpp>

Bonus::Bonus(Game* game): Entity(game)
{
	_image = std::make_unique<sf::Image>();
	bool a = _image->loadFromFile("resources/bonus.png");

	_texture = std::make_unique<sf::Texture>();
	_texture->loadFromImage(*_image);

	_sprite = std::make_unique<sf::Sprite>();
	_sprite->setTexture(*_texture);
	_sprite->setOrigin(8, 8);
	_sprite->setTextureRect(sf::IntRect(static_cast<int>(_type) * 16, 0, 16, 16));
}

void Bonus::start()
{
}

void Bonus::render(sf::RenderTarget& target)
{
	auto pos = _sprite->getPosition();
	target.draw(*_sprite);
}

void Bonus::update(float dt)
{
	_sprite->move({ 0, 100 * dt });
}
