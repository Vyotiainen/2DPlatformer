#pragma once
#include "Ammo.h"
#include "Globalvars.h"


class PistolAmmo : public Ammo
{
public:
	PistolAmmo();
	int returnID(){ return PISTOLAMMO; };
	void deleteBody(){ _body->GetWorld()->DestroyBody(_body); };
	PistolAmmo(b2World *&world, sf::Vector2f mouseCord, sf::Vector2f gunCord);
	void draw(sf::RenderWindow &window);
	void setBody(b2World *&world, sf::Vector2f mouseCord, sf::Vector2f gunCord);
	~PistolAmmo();
};

