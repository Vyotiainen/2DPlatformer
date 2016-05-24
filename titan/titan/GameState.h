#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <map>
#include "Character.h"
#include "ContactListener.h"
class Level;

class GameState
{
public:
	GameState();
	void hardInit();
	void softInit();
	void draw(sf::RenderWindow &window);
	int update();
	void checkContacts();
	void hardReset();
	void softReset();
	void hardResetDelete();
	void softResetDelete();
	virtual ~GameState();
	void updateHUD(sf::RenderWindow &window);
private:
	b2World *_world;
	Player *_player;
	Level *_currentLevel;
	sf::View *_view;

protected:
	ContactListener _listener;
};
