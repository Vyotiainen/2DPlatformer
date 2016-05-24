#pragma once
#include "Globalvars.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cmath>
#include "Drawable.h"

class Ammo : public Drawable{
protected:
	int _dmg;
	b2Body *_body;
	float velocity;
	sf::Time _lifeTime;
	sf::Clock _fireTimer;

public:
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void setBody(b2World *&world, sf::Vector2f mouseCord, sf::Vector2f gunCord) = 0;
	virtual b2Body* getBody(){ return _body; }
	virtual int getDmg() {
		return _dmg;
	}
	virtual b2Vec2 getDirection(sf::Vector2f mouseCord, sf::Vector2f gunCord) {
		b2Vec2 direction;
		float length;
		direction.x = mouseCord.x - gunCord.x;
		direction.y = mouseCord.y - gunCord.y;
		length = sqrtf(powf(direction.x, 2) + powf(direction.y, 2));

		direction.x = direction.x / length * velocity;
		direction.y = direction.y / length * velocity;

		return direction;

	}

	virtual bool inScreen(sf::RenderWindow &window) {
		sf::Vector2f ammoPos(_body->GetPosition().x * SCALE, _body->GetPosition().y * SCALE);
		sf::Vector2f win = window.getView().getCenter();
		sf::Vector2f size = window.getView().getSize();
		if ((win.x - size.x / 2) < ammoPos.x && ammoPos.x < (win.x + size.x / 2)) {
			if ((win.y - size.y / 2) < ammoPos.y && ammoPos.y < (win.y + size.y / 2)) {
				return true;
			}
			return false;
		}
		else return false;
	}

	virtual bool isAlive(){
		if (_lifeTime >= _fireTimer.getElapsedTime()) {
			return true;
		}
		return false;
	}

};