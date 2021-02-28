#pragma once
#include "Entity.h"

class Box: public Entity
{
public:
	explicit Box(Game* game);

	std::string name() override { return "box"; }

	void start() override;
	void update(float deltaTime) override;
	void onCollide(Entity* other) override;
};

