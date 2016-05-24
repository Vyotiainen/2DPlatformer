#pragma once
#include <SFML/Graphics.hpp>

class Crosshair
{
public:
	Crosshair();
	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
	sf::Vector2f getPosition(){ return _position; }
	~Crosshair();
private:
	sf::Vector2f _position;
};

