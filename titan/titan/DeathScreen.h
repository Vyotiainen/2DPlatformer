#pragma once

#include "Screen.h"

class DeathScreen : public Screen
{
public:
	DeathScreen();
	int run(sf::RenderWindow &window);
	~DeathScreen();
};

