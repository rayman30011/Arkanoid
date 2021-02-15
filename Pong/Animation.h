#pragma once
#include "SFML/Graphics.hpp"
struct Animation
{
	float speed;
	std::vector<sf::IntRect> frames;
};