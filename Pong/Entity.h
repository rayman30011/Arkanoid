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

	virtual std::string name() { return "hello"; }

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

	virtual void onCollide(Entity& other) {}
	virtual void onDestroy() {}

	virtual void setPosition(sf::Vector2f position);
	
protected:
	std::unique_ptr<sf::Sprite> _sprite;
	std::unique_ptr<sf::Image> _image;
	std::unique_ptr<sf::Texture> _texture;
	sf::FloatRect _boundRect;

	bool _isDestroyed;
};

