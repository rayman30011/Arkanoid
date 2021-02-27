#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class ResourceManager 
{
public:
	void init();
	std::shared_ptr<sf::Texture> getImage(const std::string& name);
	std::shared_ptr<sf::SoundBuffer> getSound(const std::string& name);
private:
	void tryLoadTexture(const std::string& name);
	void tryLoadSound(const std::string& name);
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
	std::map<std::string, std::shared_ptr<sf::SoundBuffer>> _sounds;
};

