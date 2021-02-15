#pragma once
#include "Entity.h"

class Ball : public Entity {
public:
	Ball(Game* game): Entity(game)
	{
		_image->loadFromFile("resources/ball.png");
		_image->createMaskFromColor(sf::Color::Green);

		_texture->loadFromImage(*_image);
		_sprite->setTexture(*_texture);

		auto size = _texture->getSize();
		_boundRect.height = size.y;
		_boundRect.width = size.x;

		_speed = 150;
	}

	void start() override {}

	void update(float delta_time) override {
		_sprite->move(_direction * _speed * delta_time);
	}

	const sf::Vector2f& get_position() { return _sprite->getPosition(); }

	float getSpeed() { return _speed; }
	void setSpeed(float value) { _speed = value; }
	
	sf::Vector2f getDirection() { return _direction; }
	void set_direction(sf::Vector2f value) { _direction = value; }

private:
	float _speed;
	sf::Vector2f _direction;
};