#include "Player.h"
#include <iostream>

int Player::_footCount = 0;

Player::Player()
{
}

Player::Player(int data, b2World *&world) {
	setHp(100);
	_lvl = 1;
	_maxHP = 100;
	_nextLvl = 1000;
	_exp = 0;
	setBody(data, world);
}

void Player::setBody(int data, b2World *&world) {
	_footCount = 0;
	_characterShape.setSize(sf::Vector2f(_size * 2, _size * 2));
	_characterShape.setFillColor(sf::Color::Magenta);

	//Define all player body attributes
	b2BodyDef playerDef;
	playerDef.position = b2Vec2(0.f, 0.f);
	playerDef.type = b2_dynamicBody;
	playerDef.fixedRotation = true;
	_body = world->CreateBody(&playerDef);
	_body->SetUserData((Drawable*)this);

	//Create and set fixtures for player body
	b2PolygonShape playerShape;
	playerShape.SetAsBox(_size / SCALE, _size / SCALE);

	b2FixtureDef playerFixtureDef;
	playerFixtureDef.density = 1.f;
	playerFixtureDef.restitution = 0.f;
	playerFixtureDef.friction = 0.5f;
	playerFixtureDef.shape = &playerShape;
	playerFixtureDef.filter.groupIndex = FRIENDLY_GROUP;
	_body->CreateFixture(&playerFixtureDef)->SetUserData((void*)(data + 1000));

	//Create and set feet for player
	b2PolygonShape footShape;
	footShape.SetAsBox((_size - 1) / SCALE, (_size) / SCALE, b2Vec2(0.f, 0.2f), 0);

	b2FixtureDef footSensorDef;
	footSensorDef.density = 0.f;
	footSensorDef.shape = &footShape;
	footSensorDef.isSensor = true;
	footSensorDef.filter.groupIndex = FRIENDLY_GROUP;
	_body->CreateFixture(&footSensorDef)->SetUserData((void*)(data + 1001));
}

void Player::draw(sf::RenderWindow &window) {

	_crosshair.draw(window);
	b2World *tmp = _body->GetWorld();
	_gun.draw(tmp, window, sf::Vector2f(SCALE * _body->GetPosition().x, SCALE * _body->GetPosition().y), _crosshair.getPosition());

	checkHp();

	_characterShape.setOutlineThickness(-5);
	_characterShape.setOutlineColor(sf::Color(0, 0, 0));
	_characterShape.setOrigin(_size, _size);
	_characterShape.setPosition(SCALE * _body->GetPosition().x, SCALE * _body->GetPosition().y);
	window.draw(_characterShape);
}

void Player::processInput(b2World *&world){

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		//add pistolAmmo to _ammos map.
		_gun.shoot(world, _crosshair.getPosition());
	}

	b2Vec2 vel = _body->GetLinearVelocity();
	float desiredVel = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		desiredVel = b2Max(vel.x + 0.1f, 10.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		desiredVel = b2Min(vel.x - 0.1f, -10.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		if (_footCount >= 1){
			_body->ApplyLinearImpulse(b2Vec2(0, _body->GetMass() * -2), _body->GetWorldCenter(), true);
		}
	}

	float velChange = desiredVel - vel.x;
	float impulse = _body->GetMass() * velChange; //disregard time factor

	//	if (_body->GetLinearVelocity().x <= 20.f && _body->GetLinearVelocity().x >= -20.f){
	_body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter(), true);
	//	}
}

int Player::getFootCount() {
	return _footCount;
}

Pistol Player::getGun() {
	return _gun;
}

void Player::setFootCount(int change) {
	if (change == 1) {
		_footCount++;
	}
	else {
		_footCount--;
	}
}

float Player::getCurHP() {
	float ret;
	ret = (float)_hp / (float)_maxHP;
	return ret;
}

int Player::getMaxHP() {
	return _maxHP;
}

float Player::getExp() {
	float ret;
	ret = (float)_exp / (float)_nextLvl;
	return ret;
}

void Player::gainExp(int exp) {
	_exp += exp;
	if (_exp >= _nextLvl) {
		_exp -= _nextLvl;
		_nextLvl += 1000;
		_maxHP += 10;
		_hp = _maxHP;
	}
}


Player::~Player()
{
}