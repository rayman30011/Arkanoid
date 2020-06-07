#include "Player.h"

Player::Player(const std::string& fileName)
{
	_image = std::make_unique<sf::Image>();
	_texture = std::make_unique<sf::Texture>();
	_sprite = std::make_unique<sf::Sprite>();

	_image->loadFromFile(fileName);
	_image->createMaskFromColor(sf::Color::Green);
	
	_texture->loadFromImage(*_image);
	_sprite->setTexture(*_texture);
	_sprite->scale(2.f, 2.f);

	_boundRect.width = _image->getSize().x * 2.f;
	_boundRect.height = _image->getSize().y * 2.f;
}

void Player::update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		move({ -200 * deltaTime, 0 });
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		move({ 200 * deltaTime, 0 });
	}
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(*_sprite);
}

void Player::setPosition(sf::Vector2f position)
{
	_boundRect.left = position.x;
	_boundRect.top = position.y;

	_sprite->setPosition(position);
}

void Player::move(sf::Vector2f direction)
{
	_sprite->move(direction);
	auto position = _sprite->getPosition();
	_boundRect.left = position.x;
	_boundRect.top = position.y;
}
