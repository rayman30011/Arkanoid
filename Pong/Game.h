#pragma once

#include <SFML/Graphics.hpp>
#include "MapRenderer.h"

class Ball;
class Player;
class Entity;

class Game
{
public:
	enum class State {
		Idle,
		Running,
		Win,
		Lose
	};
public:
	Game(sf::Vector2u windowSize);
	void init();
	void update(float time);
	void render(sf::RenderTarget& target);

	sf::IntRect getMapRect() { return _mapRect; }
private:
	void restart();
private:
	State _currentState;
	Map* _currentMap;
	MapRenderer* _mapRenderer;

	std::string _fileName;
	sf::Vector2u _windowSize;
	Ball* _ball;
	Player* _player;
	std::vector<Entity*> _entities;

	sf::Text _scoreText;
	sf::Font* _font;

	uint32_t _score;
	sf::IntRect _mapRect;
	sf::Texture _bgTexture;
	sf::Sprite _bgSprite;
	sf::Shader _crtShader;

	bool _isBallFollow;
	int lives;
};

