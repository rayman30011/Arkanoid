#pragma once
#include "Entity.h"
class Slime : public Entity
{
public:
	Slime(Game* game);
	void start() override;
	void render(sf::RenderTarget& target) override;
	void update(float deltaTime) override;
private:
	sf::Vector2f _target;
};

