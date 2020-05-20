#pragma once
#include <SFML/Graphics.hpp>

#include "Map.h"

class MapRenderer
{
public:
	MapRenderer(Map* map);
	void set_screen_size(sf::Vector2u size) {
		_screen_size = size;
	}

	void render(sf::RenderTarget& target);
private:
	void renderBlock(Block& block);
private:
	sf::Vector2u _screen_size;
	Map* _map;
	sf::Image* _image;
	sf::Texture* _texture;
	sf::Sprite* _sprite;
};

