#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Level.h"
#include "Character.h"

typedef std::map<int, Character*> characterMap;
class FirstLevel : public Level
{
public:
	FirstLevel(b2World *&world, Player *&player);
	void loadLevel(b2World *&world, Player *&player);
	void loadTextures();
	void draw(sf::RenderWindow &window);
	void update(b2World *&world, b2Vec2 playerPos);
	~FirstLevel();
private:
	b2Body* _groundBody;
	std::list<Character*> _deleteList;
	b2World *_world;

	sf::Texture *grassTexture;
	sf::Texture *dirtTexture;
	sf::Texture *skyTexture;
};

