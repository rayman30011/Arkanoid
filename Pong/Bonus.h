#pragma once
#include "memory"
#include <SFML/Graphics.hpp>

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

	void setType(Type type) { _type = type; }
	Type getType() const { return _type; }
	
	void start() override;
	void update(float dt) override;
	void render(sf::RenderTarget& target) override;

private:

	Type _type;
};

