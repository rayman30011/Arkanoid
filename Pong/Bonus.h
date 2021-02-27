#pragma once

#include "Entity.h"

class Bonus : public Entity
{
public:
	enum class Type 
	{
		None = -1,
		Double,
		SpeedUp,
		SpeedDown,
		SizeUp,
		SizeDown,
	};

	Bonus(Game* game);

	std::string name() override { return "bonus"; }
	
	void setType(Type type) { _type = type; }
	Type getType() const { return _type; }
	
	void start() override;
	void update(float dt) override;
	void onCollide(Entity* other) override;

	void doubleBall();

private:
	Type _type;
};

