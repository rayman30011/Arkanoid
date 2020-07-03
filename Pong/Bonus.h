#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class Bonus
{
public:
	enum class Type 
	{
		None = -1,
		Double,
		SpeedUp,
		SpeedDown,
		SizeUp,
		SizeDown,
	};

	Bonus(Type type);

	void start();
	void update(float dt);
	void draw(sf::RenderTarget& target);

private:
	std::unique_ptr<sf::Image> _image;
	std::unique_ptr<sf::Texture> _texture;
	std::unique_ptr<sf::Sprite> _sprite;

	Type _type;
};

