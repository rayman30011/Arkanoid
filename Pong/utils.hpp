#pragma once
#include <SFML/System.hpp>

inline float len(sf::Vector2f& vec)
{
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

inline void normilize(sf::Vector2f& vec)
{
	float lenght = len(vec);
	vec.x /= lenght;
	vec.y /= lenght;
}
