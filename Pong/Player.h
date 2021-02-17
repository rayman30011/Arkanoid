#pragma once
#include "Entity.h"
#include "Game.h"

class Player : public Entity
{
public:
	Player(Game* game);
	void start() override;
	void update(float deltaTime) override;
private:
	void move(sf::Vector2f direction);
};

