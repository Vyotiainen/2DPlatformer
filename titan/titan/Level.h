#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <fstream>
#include <stdio.h>
#include "Globalvars.h"
#include "Player.h"

class Level
{
public:
	virtual void loadLevel(b2World *&world, Player *&player) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void update(b2World *&world, b2Vec2 playerPos) = 0;
protected:
	std::vector<int> width;
	int height;
	char **_tileMap;
};

