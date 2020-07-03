#include "Bonus.h"

Bonus::Bonus(Type type) : _type(type)
{
	_image = std::make_unique<sf::Image>();
	bool a = _image->loadFromFile("resources/bonus.png");

	_texture = std::make_unique<sf::Texture>();
	_texture->loadFromImage(*_image);

	_sprite = std::make_unique<sf::Sprite>();
	_sprite->setTexture(*_texture);
	_sprite->scale(2.f, 2.f);

	_sprite->setPosition({ 100, 100 });
}

void Bonus::start()
{
	int offsetX = static_cast<int>(_type);
	_sprite->setTextureRect(sf::IntRect(offsetX * 16, 0, 16, 16));
}

void Bonus::draw(sf::RenderTarget& target)
{
	target.draw(*_sprite);
}

void Bonus::update(float dt)
{
	_sprite->move({ 0, 100 * dt });
}
