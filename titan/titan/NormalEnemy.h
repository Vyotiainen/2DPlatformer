#pragma once

#include "Character.h"

class NormalEnemy : public Character
{
public:
	NormalEnemy();
	int returnID(){ return NORMALENEMY; };
	void deleteBody(){ _body->GetWorld()->DestroyBody(_body); };
	NormalEnemy(int data, b2World *&world, int x, int y);
	void setBody(int data, b2World *&world);
	void draw(sf::RenderWindow &window);
	void update(b2World *&world, b2Vec2 playerPos);
	Pistol getGun(){ Pistol gun; return gun; }
	~NormalEnemy();
private:
	sf::Clock _patrolTimer;
	sf::Time _patrolDelay;
	int direction;
};

