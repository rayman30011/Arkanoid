#pragma once
#include "Entity.h"
class Slime : public Entity
{
public:
	Slime(Game* game);
	void start() override;
	void update(float deltaTime) override;

private:
	void retarget();
private:
	sf::Vector2f _target;
	float _speed;
};

