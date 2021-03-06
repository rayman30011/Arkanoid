#pragma once
#include "Entity.h"

class Ball : public Entity {
public:
	Ball(Game* game): Entity(game)
	{
		auto manager = game->getResourceManager();
		auto texture = manager.getImage("resources/ball.png");
		_sprite->setTexture(*texture.get());

		auto size = texture->getSize();
		_boundRect.height = size.y;
		_boundRect.width = size.x;
		_speed = 150;
		
		setCollidable(true);
	}

	std::string name() override { return "ball"; }

	void start() override
	{
		setCollidable(true);
	}

	void update(float delta_time) override;

	float getSpeed() { return _speed; }
	void setSpeed(float value) { _speed = value; }
	
	sf::Vector2f getDirection() { return _direction; }
	void set_direction(sf::Vector2f value) { _direction = value; }

private:
	float _speed;
	sf::Vector2f _direction;
};