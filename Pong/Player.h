#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(const std::string& fileName);
	void update(float deltaTime);
	void render(sf::RenderTarget& target);

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() { return _sprite->getPosition(); }

	sf::FloatRect getBoundRect() { return _boundRect; }
private:
	void move(sf::Vector2f direction);
private:
	std::unique_ptr<sf::Sprite> _sprite;
	std::unique_ptr<sf::Image> _image;
	std::unique_ptr<sf::Texture> _texture;

	sf::FloatRect _boundRect;
};

