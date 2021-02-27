#pragma once
#include "Entity.h"
#include "Animator.h"

class Slime : public Entity
{
public:
	Slime(Game* game);

	std::string name() override { return "slime"; }
	
	void start() override;
	void update(float deltaTime) override;
	void onCollide(Entity* other) override;

private:
	void retarget();

private:
	sf::Vector2f _target;
	float _speed;

	Animator _animator;
};

