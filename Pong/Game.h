#pragma once

#include <SFML/Graphics.hpp>

#include "Ball.hpp"
#include "Player.h"
#include "MapRenderer.h"

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
	State _currentState;
	Map* _currentMap;
	MapRenderer* _mapRenderer;

	std::string _fileName;
	sf::Vector2u _windowSize;
	std::unique_ptr<Ball> _ball;
	std::unique_ptr<Player> _player;

	sf::Text _scoreText;
	sf::Font* _font;

	uint32_t _score;

	bool _isBallFollow;
};

