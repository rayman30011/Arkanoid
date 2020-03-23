#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	void setPosition(const sf::Vector2f& value) { _sprite.setPosition(value); }
	const sf::Vector2f& getPosition() { return _sprite.getPosition(); }

	sf::Sprite& getSprite() { return _sprite; }
	void setSprite(sf::Sprite& value) { _sprite = value; }
	virtual void render(sf::RenderTarget& target);
private:
	sf::Sprite _sprite;
};

