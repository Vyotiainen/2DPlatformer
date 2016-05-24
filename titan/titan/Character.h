#pragma once

#include "Globalvars.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>
#include <stdlib.h>
#include "Pistol.h"
#include "Drawable.h"

class Character : public Drawable {

protected:
	float _size = 25;
	int _hp;
	b2Body *_body;
	sf::RectangleShape _characterShape;

public:

	virtual void setBody(int data, b2World *&world) = 0;
	virtual void takeDmg(int dmg) { _hp = _hp - dmg; }
	virtual void setHp(int hp) { _hp = hp; }
	virtual void checkHp(){
		if (_hp <= 80 && _hp > 20){
			_characterShape.setFillColor(sf::Color::Yellow);
		}
		else if (_hp <= 20 && _hp > 0){
			_characterShape.setFillColor(sf::Color::Red);
		}
	}
	virtual int getHp() { return _hp; }
	virtual b2Body* getBody(){ return _body; }
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void update(b2World *&world, b2Vec2 playerPos){};
	virtual Pistol getGun() = 0;
};