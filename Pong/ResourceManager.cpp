#include "ResourceManager.h"
#include <iostream>

void ResourceManager::init()
{
	tryLoadTexture("resources/ball.png");
	tryLoadSound("resources/sounds/hit_block.wav");
}

std::shared_ptr<sf::Texture> ResourceManager::getImage(const std::string& name)
{
	return _textures[name];
}

std::shared_ptr<sf::SoundBuffer> ResourceManager::getSound(const std::string& name)
{
	return _sounds[name];
}

void ResourceManager::tryLoadTexture(const std::string& name)
{
	auto img = std::make_shared<sf::Texture>();
	if (!img->loadFromFile(name))
	{
		std::cerr << "Error load image: " << name << std::endl;
 		throw;
	}
	_textures[name] = img;
}

void ResourceManager::tryLoadSound(const std::string& name)
{
	auto sound = std::make_shared<sf::SoundBuffer>();
	if (!sound->loadFromFile(name))
	{
		std::cerr << "Error load sound: " << name << std::endl;
		throw;
	}
	_sounds[name] = sound;
}
