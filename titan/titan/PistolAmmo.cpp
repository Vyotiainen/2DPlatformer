#include "PistolAmmo.h"


PistolAmmo::PistolAmmo()
{
}

PistolAmmo::PistolAmmo(b2World *&world, sf::Vector2f mouseCord, sf::Vector2f gunCord) {
	_lifeTime = sf::Time(sf::seconds(3.f));
	setBody(world, mouseCord, gunCord);
}

void PistolAmmo::draw(sf::RenderWindow &window) {
	sf::CircleShape bulletShape(6);
	bulletShape.setFillColor(sf::Color::Blue);
	bulletShape.setOrigin(6, 6);
	bulletShape.setPosition(SCALE * _body->GetPosition().x, SCALE * _body->GetPosition().y);
	window.draw(bulletShape);
}


void PistolAmmo::setBody(b2World *&world, sf::Vector2f mouseCord, sf::Vector2f gunCord){
	velocity = 70;
	_dmg = 20;

	b2Vec2 direction = getDirection(mouseCord, gunCord);

	//bulletbody
	b2Vec2 pos(gunCord.x / SCALE, gunCord.y / SCALE);
	b2BodyDef bulletDef;
	bulletDef.bullet = true;
	bulletDef.gravityScale = 0;
	bulletDef.position = pos;
	bulletDef.type = b2_dynamicBody;
	_body = world->CreateBody(&bulletDef);
	_body->SetUserData((Drawable *)this);
	_body->SetLinearVelocity(direction);

	//bulletfixture and shape
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 6 / SCALE;

	b2FixtureDef fixDef;
	fixDef.shape = &circleShape;
	fixDef.density = 0.000001f;
	fixDef.friction = 0;
	fixDef.restitution = 0;
	fixDef.filter.groupIndex = FRIENDLY_GROUP;
	_body->CreateFixture(&fixDef)->SetUserData((void*)this);

}

PistolAmmo::~PistolAmmo()
{

}
