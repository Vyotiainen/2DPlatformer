#pragma once
#include "Screen.h"

class PauseScreen : public Screen
{
public:
	PauseScreen();
	int run(sf::RenderWindow &window);
	~PauseScreen();
};

