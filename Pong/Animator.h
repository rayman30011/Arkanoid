#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Animator
{
public:
	Animator(sf::Sprite* sprite);
	void update(float dt);
	void setAnimation(std::string name);
	void addAnimation(std::string, Animation animation);

	void play();
	void stop();

private:
	sf::Sprite* _sprite;
	float _currentTime;
	Animation* _currentAnimation;
	std::map<std::string, Animation> _animations;

	bool _isStoped;
};

