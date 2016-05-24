#include "Crosshair.h"
#include <iostream>

Crosshair::Crosshair()
{
}

void Crosshair::update(sf::RenderWindow &window){
	_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void Crosshair::draw(sf::RenderWindow &window){
	update(window);
	sf::RectangleShape rectGround(sf::Vector2f(10, 10));
	rectGround.setOutlineThickness(-5);
	rectGround.setFillColor(sf::Color::Green);
	rectGround.setOutlineColor(sf::Color::Black);
	rectGround.setOrigin(5, 5);
	rectGround.setPosition(_position.x, _position.y);
	window.draw(rectGround);
}


Crosshair::~Crosshair()
{
}
