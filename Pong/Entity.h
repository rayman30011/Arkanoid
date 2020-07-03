#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity() {
		_image = std::make_unique<sf::Image>();
		_texture = std::make_unique<sf::Texture>();
		_sprite = std::make_unique<sf::Sprite>();
	}

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

	virtual void onCollide(Entity& other) {}
	virtual void onDestroy() {}
	
protected:
	std::unique_ptr<sf::Sprite> _sprite;
	std::unique_ptr<sf::Image> _image;
	std::unique_ptr<sf::Texture> _texture;
};

