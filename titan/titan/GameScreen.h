#pragma once
#include "Screen.h"
#include "GameState.h"

class GameScreen : public Screen
{
public:
	GameScreen();
	int run(sf::RenderWindow &window);
	~GameScreen();
private:
	static const sf::Time TimePerFrame;
	GameState _gameState;
};

