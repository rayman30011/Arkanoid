#include "Player.h"

Player::Player(Game* game): Entity(game)
{
	_image->loadFromFile("resources/deck.png");
	_image->createMaskFromColor(sf::Color::Green);
	
	_texture->loadFromImage(*_image);
	_sprite->setTexture(*_texture);

	_boundRect.width = _image->getSize().x;
	_boundRect.height = _image->getSize().y;

	setCollidable(true);
}

void Player::start()
{
	
}

void Player::update(float deltaTime)
{
	auto currentPosition = _sprite->getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		currentPosition += { -200 * deltaTime, 0 };
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		currentPosition += { 200 * deltaTime, 0 };
	}

	const auto mapRect = getGame()->getMapRect();
	const auto& playerRect = _sprite->getTextureRect();

	if (currentPosition.x > mapRect.left && (currentPosition.x + playerRect.width) < (mapRect.width + mapRect.left))
	{
		setPosition(currentPosition);
	}
}

void Player::move(sf::Vector2f direction)
{
	_sprite->move(direction);
	auto position = _sprite->getPosition();
	_boundRect.left = position.x;
	_boundRect.top = position.y;
}
