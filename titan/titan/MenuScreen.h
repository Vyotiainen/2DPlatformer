#pragma once
#include "Screen.h"

class MenuScreen : public Screen
{
public:
	MenuScreen();
	int run(sf::RenderWindow &window);
	~MenuScreen();
};

