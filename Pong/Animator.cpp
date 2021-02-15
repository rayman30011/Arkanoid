#include "Animator.h"

Animator::Animator(sf::Sprite* sprite)
	: _sprite(sprite), _currentTime(0), _isStoped(true)
{
	_currentAnimation = nullptr;
}

void Animator::update(float dt)
{
	if (_currentAnimation != nullptr && !_isStoped)
	{
		_currentTime += _currentAnimation->speed * dt;
		auto frames = _currentAnimation->frames;
		auto frameIndex = static_cast<int>(_currentTime) % frames.size();
		auto frame = frames[frameIndex];
		_sprite->setTextureRect(frame);
	}
}

void Animator::setAnimation(std::string name)
{
	_currentAnimation = &_animations[name];
	_currentTime = 0.f;
}

void Animator::addAnimation(std::string name, Animation animation)
{
	_animations[name] = animation;
}

void Animator::play()
{
	_isStoped = false;
}

void Animator::stop()
{
	_isStoped = true;
}
