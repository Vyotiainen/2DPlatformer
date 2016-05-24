#pragma once
#include "Screen.h"

class SplashScreen : public Screen
{
public:
	SplashScreen();
	int run(sf::RenderWindow &window);
	~SplashScreen();
};

