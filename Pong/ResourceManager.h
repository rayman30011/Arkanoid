#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class ResourceManager 
{
public:
	void init();
	std::shared_ptr<sf::Texture> getImage(const std::string& name);
private:
	void tryLoadTexture(const std::string& name);
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
};

