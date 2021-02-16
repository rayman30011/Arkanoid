#pragma once
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Constants.h"

class Entity
{
public:
	
	Entity(Game* game): _game(game)
	{
		_image = std::make_unique<sf::Image>();
		_texture = std::make_unique<sf::Texture>();
		_sprite = std::make_unique<sf::Sprite>();
	}

	virtual std::string name() { return "hello"; }

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderTarget& target);

	virtual void onCollide(Entity& other) {}
	virtual void onDestroy() {}

	virtual void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() { return _sprite->getPosition(); }

	sf::FloatRect getBoundRect() const;

	Game* getGame() { return _game; }

	void destroy();
	bool isDestroyed() const { return _isDestroyed; }

	bool isCollidable() const { return _isCollidable; }
	void setCollidable(bool value) { _isCollidable = value; }

	constants::Layer getLayer() const { return _layer; }
	void setLayer(constants::Layer value) { _layer = value; }
protected:
	std::unique_ptr<sf::Sprite> _sprite;
	std::unique_ptr<sf::Image> _image;
	std::unique_ptr<sf::Texture> _texture;
	sf::FloatRect _boundRect;
	Game* _game;

	bool _isDestroyed;
	bool _isCollidable;
	constants::Layer _layer;
};

