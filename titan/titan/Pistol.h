#pragma once
#include "Gun.h"
#include "Ammo.h"
#include <list>
class Pistol : public Gun
{
public:
	Pistol();
	void draw(b2World *&world, sf::RenderWindow &window, sf::Vector2f playerPos, sf::Vector2f crosshairPos);
	float coordsToAngle(sf::Vector2f playerPos, sf::Vector2f crosshairPos);
	void shoot(b2World *&world, sf::Vector2f crosshairPos);
	sf::Vector2f setBarrel(sf::Vector2f playerPos, sf::Vector2f crosshairPos);
	~Pistol();
private:
	std::list<Ammo*> _deleteList;
	float _length = 80;
};

