#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <Box2D/Box2D.h>


class Gun
{
public:
	virtual void draw(b2World *&world, sf::RenderWindow &window, sf::Vector2f playerPos, sf::Vector2f crosshairPos) = 0;
	virtual sf::Vector2f getCoords(){ return _coords; }

protected:
	sf::Vector2f _coords;
	sf::Time _firerate;
	sf::Clock _fireTimer;
};

