#include "ResourceManager.h"
#include <iostream>

void ResourceManager::init()
{
	tryLoadTexture("resources/ball.png");
}

std::shared_ptr<sf::Texture> ResourceManager::getImage(const std::string& name)
{
	return _textures[name];
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
