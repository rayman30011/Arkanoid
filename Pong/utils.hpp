#pragma once
#include <SFML/System.hpp>

namespace utils
{
	inline float len(sf::Vector2f& vec)
	{
		return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	}

	inline void normalize(sf::Vector2f& vec)
	{
		const float length = len(vec);
		vec.x /= length;
		vec.y /= length;
	}
}
