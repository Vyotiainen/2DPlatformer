#include "Pistol.h"
#include "Globalvars.h"
#include "PistolAmmo.h"
#include <cmath>

#include "Player.h"

Pistol::Pistol(){
	_firerate = sf::Time(sf::seconds(0.4f));
}

void Pistol::draw(b2World *&world, sf::RenderWindow &window, sf::Vector2f playerPos, sf::Vector2f crosshairPos){
	float angle = coordsToAngle(playerPos, crosshairPos);

	sf::RectangleShape gunRect(sf::Vector2f(_length, 10));
	gunRect.setFillColor(sf::Color::Green);
	gunRect.setOutlineThickness(-2);
	gunRect.setOutlineColor(sf::Color(0, 0, 0));
	gunRect.setOrigin(0, 10 / 2);
	gunRect.setPosition(playerPos.x, playerPos.y);
	gunRect.rotate(angle);

	_coords = gunRect.getPosition() + setBarrel(gunRect.getPosition(), crosshairPos);
	window.draw(gunRect);

	PistolAmmo *bullet;
	for (b2Body* ammo = world->GetBodyList(); ammo; ammo = ammo->GetNext()) {
		if (ammo->GetType() == b2_dynamicBody) {
			int type = static_cast<Drawable*>(ammo->GetUserData())->returnID();

			switch (type) {
			case PISTOLAMMO:
				bullet = static_cast<PistolAmmo*>((Drawable*)(ammo->GetUserData()));
				if (bullet->isAlive() && bullet->inScreen(window)){
					bullet->draw(window);
				}
				else{
					_deleteList.push_back(bullet);
				}
				break;
			default: break;
			}
		}
	}

	for (std::list<Ammo*>::iterator it = _deleteList.begin(); it != _deleteList.end(); it++){
		((Ammo*)*it)->getBody()->GetWorld()->DestroyBody(((Ammo*)*it)->getBody());
		delete *it;
	}
	_deleteList.clear();
}


float Pistol::coordsToAngle(sf::Vector2f playerPos, sf::Vector2f crosshairPos){
	float angle;

	angle = (float)(atan2f(crosshairPos.y - playerPos.y, crosshairPos.x - playerPos.x) * 180 / PI);

	return angle;
}

sf::Vector2f Pistol::setBarrel(sf::Vector2f playerPos, sf::Vector2f crosshairPos) {
	sf::Vector2f direction;
	float vec1;
	direction.x = crosshairPos.x - playerPos.x;
	direction.y = crosshairPos.y - playerPos.y;
	vec1 = sqrtf(powf(direction.x, 2) + powf(direction.y, 2));
	direction.x = direction.x / vec1 * _length;
	direction.y = direction.y / vec1 * _length;
	return direction;
}

void Pistol::shoot(b2World *&world, sf::Vector2f crosshairPos){

	if (_fireTimer.getElapsedTime() >= _firerate){
		new PistolAmmo(world, crosshairPos, getCoords());
		_fireTimer.restart();
	}
}

Pistol::~Pistol()
{
}
