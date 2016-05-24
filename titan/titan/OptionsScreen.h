#pragma once

#include "Screen.h"

class OptionsScreen : Screen
{
public:
	OptionsScreen();
	int run(sf::RenderWindow &window);
	~OptionsScreen();
};

