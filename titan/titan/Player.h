#pragma once
#include "Character.h"
#include "Crosshair.h"


class Player : public Character
{
private:
	Crosshair _crosshair;
	Pistol _gun;
	static int _footCount;
	int _lvl;
	int _maxHP;
	int _nextLvl;
	int _exp;
	float _endCoord;

public:
	Player();
	int returnID(){ return PLAYER; };
	void deleteBody(){ _body->GetWorld()->DestroyBody(_body); };
	Player(int data, b2World *&world);
	void setBody(int data, b2World *&world);
	void draw(sf::RenderWindow &window);

	int getFootCount();
	void setFootCount(int change);

	float getCurHP();
	int getMaxHP();

	float getExp();
	void gainExp(int exp);

	void setPos(int x, int y){
		_body->SetTransform(b2Vec2((TILESIZE*(float)x) / SCALE, (100 + TILESIZE*(float)y) / SCALE), _body->GetAngle());
	};

	void setEnd(float x){
		_endCoord = x;
	};

	float getEnd(){
		return _endCoord;
	};

	void processInput(b2World *&world);
	Pistol getGun();
	~Player();
};

