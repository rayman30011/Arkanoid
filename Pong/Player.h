#pragma once
#include "Entity.h"
#include "Game.h"

class Player : public Entity
{
public:
	Player(Game* game);
	void start() override {};
	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;

	void setPosition(sf::Vector2f position) override;
	sf::Vector2f getPosition() { return _sprite->getPosition(); }

	sf::FloatRect getBoundRect() { return _boundRect; }
private:
	void move(sf::Vector2f direction);
private:
	sf::FloatRect _boundRect;
};

