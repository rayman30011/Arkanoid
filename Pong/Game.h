#pragma once

#include <SFML/Graphics.hpp>

#include "Ball.hpp"
#include "Player.h"
#include "MapRenderer.h"
#include "Bonus.h"

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

	void restart();
private:
	//void updateTimers(float time);
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
	sf::RectangleShape _background;

	bool _isBallFollow;
	int lives;
};

