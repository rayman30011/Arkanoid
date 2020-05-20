#pragma once
#include <SFML/Graphics.hpp>

class Ball {
public:
	Ball(const std::string& file_name) {
		_img = new sf::Image();
		_img->loadFromFile(file_name);
		_img->createMaskFromColor(sf::Color::Green);

		_texture = new sf::Texture();
		_texture->loadFromImage(*_img);

		_sprite.setTexture(*_texture);
		_sprite.scale(2.f, 2.f);

		auto size = _texture->getSize();
		_sprite.setOrigin(size.x / 2, size.y / 2);
		_speed = 250;
	}

	void update(float delta_time) {
		_sprite.move(_direction * _speed * delta_time);
	}

	void draw(sf::RenderTarget& const target) const {
		target.draw(_sprite);
	}

	void set_position(sf::Vector2f const& position) {
		_sprite.setPosition(position);
	}

	const sf::Vector2f& get_position() { return _sprite.getPosition(); }

	float get_speed() { return _speed; }
	void set_speed(float value) { _speed = value; }
	
	sf::Vector2f get_direction() { return _direction; }
	void set_direction(sf::Vector2f value) { _direction = value; }

	~Ball() {
		delete _img;
		delete _texture;
	}

private:
	float _speed;

	sf::Sprite _sprite;
	sf::Image* _img;
	sf::Texture* _texture;

	sf::Vector2f _direction;
};