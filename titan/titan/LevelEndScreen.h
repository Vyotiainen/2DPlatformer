#pragma once

#include "Screen.h"

class LevelEndScreen : public Screen
{
public:
	LevelEndScreen();
	int run(sf::RenderWindow &window);
	~LevelEndScreen();
};

