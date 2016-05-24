#include "NormalEnemy.h"


NormalEnemy::NormalEnemy()
{
}

NormalEnemy::NormalEnemy(int data, b2World *&world, int x, int y) {

	_characterShape.setSize(sf::Vector2f(_size * 2, _size * 2));
	_characterShape.setFillColor(sf::Color::Green);

	//Define all Enemy body attributes
	b2BodyDef enemyDef;
	enemyDef.position = b2Vec2((TILESIZE*x) / SCALE, (100 + TILESIZE*y) / SCALE);
	enemyDef.type = b2_dynamicBody;
	_body = world->CreateBody(&enemyDef);
	_body->SetUserData((Drawable *)this);

	//Create and set fixtures for enemy body
	b2PolygonShape enemyShape;
	enemyShape.SetAsBox(_size / SCALE, _size / SCALE);

	b2FixtureDef enemyFixtureDef;
	enemyFixtureDef.density = 1.f;
	enemyFixtureDef.restitution = 0.f;
	enemyFixtureDef.friction = 0.5f;
	enemyFixtureDef.shape = &enemyShape;
	_body->CreateFixture(&enemyFixtureDef)->SetUserData((void*)(data + 1000));

	setHp(100);

	_patrolDelay = sf::Time(sf::seconds(1.5f));
	_patrolTimer.restart();
	direction = 1;
}

void NormalEnemy::setBody(int data, b2World *&world) {
	_characterShape.setSize(sf::Vector2f(_size * 2, _size * 2));
	_characterShape.setFillColor(sf::Color::Green);

	//Define all Enemy body attributes
	b2BodyDef enemyDef;
	enemyDef.position = b2Vec2(15.f, 0.f);
	enemyDef.type = b2_dynamicBody;
	_body = world->CreateBody(&enemyDef);
	_body->SetUserData((Drawable *)this);

	//Create and set fixtures for enemy body
	b2PolygonShape enemyShape;
	enemyShape.SetAsBox(_size / SCALE, _size / SCALE);

	b2FixtureDef enemyFixtureDef;
	enemyFixtureDef.density = 1.f;
	enemyFixtureDef.restitution = 0.f;
	enemyFixtureDef.friction = 0.5f;
	enemyFixtureDef.shape = &enemyShape;
	_body->CreateFixture(&enemyFixtureDef)->SetUserData((void*)(data + 1000));

	setHp(100);
}

void NormalEnemy::draw(sf::RenderWindow &window) {

	checkHp();

	_characterShape.setOutlineThickness(-5);
	_characterShape.setOutlineColor(sf::Color(0, 0, 0));
	_characterShape.setOrigin(_size, _size);
	_characterShape.setPosition(SCALE * _body->GetPosition().x, SCALE * _body->GetPosition().y);

	window.draw(_characterShape);
}

void NormalEnemy::update(b2World *&world, b2Vec2 playerPos){
	b2Vec2 vel = _body->GetLinearVelocity();

	if (_patrolTimer.getElapsedTime() >= _patrolDelay){
		_patrolTimer.restart();
		direction *= -1;
	}

	float desiredVel = 0;
	if (abs(playerPos.x - _body->GetPosition().x / SCALE) <= 0.4){
		if ((playerPos.x - _body->GetPosition().x / SCALE) < 0)
			desiredVel = b2Max(vel.x - 0.1f, -7.0f);
		else
			desiredVel = b2Max(vel.x + 0.1f, 7.0f);
	}
	else if (direction == 1){
		desiredVel = b2Max(vel.x + 0.1f, 7.0f);
	}
	else if (direction == -1) {
		desiredVel = b2Min(vel.x - 0.1f, -7.0f);
	}

	float velChange = desiredVel - vel.x;
	float impulse = _body->GetMass() * velChange; //disregard time factor
	_body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter(), true);
}

NormalEnemy::~NormalEnemy()
{
}
