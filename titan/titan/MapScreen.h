#pragma once
#include "Screen.h"

class MapScreen : public Screen
{
public:
	MapScreen();
	int run(sf::RenderWindow &window);
	~MapScreen();
};

