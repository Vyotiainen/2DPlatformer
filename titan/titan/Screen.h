#pragma once

#include <SFML/Graphics.hpp>

class Screen
{
public:
	virtual int run(sf::RenderWindow &window) = 0;
	enum screens { SPLASH, MENU, MAP, GAME, PAUSE, DEATH, END };
};