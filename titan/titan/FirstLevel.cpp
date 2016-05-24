#include "FirstLevel.h"
#include "NormalEnemy.h"
#include "Player.h"

#include <iostream>
FirstLevel::FirstLevel(b2World *&world, Player *&player)
{
	loadLevel(world, player);
	loadTextures();
}

//Create the level to the b2World world
void FirstLevel::loadLevel(b2World *&world, Player *&player){
	std::ifstream inFile("kenttahahmottelu.txt");
	height = 0;
	std::string line;

	//check width and length
	while (std::getline(inFile, line)) {
		width.push_back(line.size());
		height++;
	}
	inFile.clear();
	inFile.seekg(0, inFile.beg);

	//have to flip whole tileMap, now height = width
	_tileMap = new char *[height];
	char c = inFile.get();
	if (c != EOF) {

		for (int i = 0; i < height; i++) {
			_tileMap[i] = new char[width.at(0)];
			for (int j = 0; j <= width.at(0); j++) {
				_tileMap[i][j] = c;
				inFile.get(c);
			}
		}
	}

	b2BodyDef groundBodyDef;
	b2PolygonShape groundShape;
	b2FixtureDef groundFixtureDef;
	int data = 12;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width.at(0); j++) {
			if (_tileMap[i][j] == '0' || _tileMap[i][j] == '1') {
				float length = 1;
				groundBodyDef.position = b2Vec2((TILESIZE*j) / SCALE, (100 + TILESIZE*i) / SCALE);
				groundBodyDef.type = b2_staticBody;

				while (_tileMap[i][j + 1] == '0' || _tileMap[i][j + 1] == '1') {
					length++;
					j++;
				}

				if (length > 1) {
					groundBodyDef.position = b2Vec2((TILESIZE*j - (length*TILESIZE / 2.f) + (TILESIZE / 2.f)) / SCALE, (100 + TILESIZE*i) / SCALE);
				}

				_groundBody = world->CreateBody(&groundBodyDef);
				groundShape.SetAsBox((TILESIZE*length / 2) / SCALE, (TILESIZE / 2) / SCALE);
				groundFixtureDef.shape = &groundShape;
				groundFixtureDef.filter.groupIndex = GROUND_GROUP;
				groundFixtureDef.density = 0.f;
				groundFixtureDef.restitution = 0.f;
				groundFixtureDef.friction = 0.f;
				b2Fixture *ground;
				ground = _groundBody->CreateFixture(&groundFixtureDef);
				ground->SetUserData((void *)1010);
			}
			else if (_tileMap[i][j] == 'X') {
				data++;
				new NormalEnemy(data, world, j, i);
			}
			else if (_tileMap[i][j] == 'S') {
				player->setPos(j, i);
			}
			else if (_tileMap[i][j] == 'E') {
				player->setEnd((100 + TILESIZE*(float)j) / SCALE);
			}
		}
	}
	_world = world;
}

void FirstLevel::draw(sf::RenderWindow &window){

	sf::RectangleShape rectGround(sf::Vector2f(TILESIZE, TILESIZE));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width.at(0); j++) {

			if (_tileMap[i][j] == '0') {
				rectGround.setTexture(grassTexture);
				rectGround.setOrigin((TILESIZE / 2), (TILESIZE / 2));
				rectGround.setPosition(TILESIZE*j, 100 + TILESIZE*i);
				window.draw(rectGround);
			}
			else if (_tileMap[i][j] == '1') {
				rectGround.setTexture(dirtTexture);
				rectGround.setOrigin((TILESIZE / 2), (TILESIZE / 2));
				rectGround.setPosition(TILESIZE*j, 100 + TILESIZE*i);
				window.draw(rectGround);
			}
		}
	}

	Character *tmpEnemy;
	for (b2Body* enemy = _world->GetBodyList(); enemy; enemy = enemy->GetNext()) {
		if (enemy->GetType() == b2_dynamicBody) {
			int type = static_cast<Drawable*>(enemy->GetUserData())->returnID();

			switch (type) {
			case NORMALENEMY:
				tmpEnemy = static_cast<Character*>((Drawable*)(enemy->GetUserData()));
				tmpEnemy->draw(window);
				break;
			default: break;
			}
		}
	}
}

void FirstLevel::loadTextures(){
	grassTexture = new sf::Texture();

	if (!grassTexture->loadFromFile("textures/blocks/grass_side.png"))
	{
		std::cerr << "Error loading grass_side.png" << std::endl;
	}

	dirtTexture = new sf::Texture();

	if (!dirtTexture->loadFromFile("textures/blocks/dirt.png"))
	{
		std::cerr << "Error loading dirt.png" << std::endl;
	}

	skyTexture = new sf::Texture();

	if (!skyTexture->loadFromFile("textures/environment/end_sky.png"))
	{
		std::cerr << "Error loading end_sky.png" << std::endl;
	}
}

void FirstLevel::update(b2World *&world, b2Vec2 playerPos){
	Character *tmp;
	for (b2Body* it = world->GetBodyList(); it; it = it->GetNext()) {
		if (it->GetType() == b2_dynamicBody) {
			int type = static_cast<Drawable*>(it->GetUserData())->returnID();

			switch (type) {
			case NORMALENEMY:
				tmp = static_cast<Character*>((Drawable*)(it->GetUserData()));
				tmp->update(world, playerPos);
				break;
			default: break;
			}
		}
	}
}

FirstLevel::~FirstLevel()
{
	delete skyTexture;
	delete dirtTexture;
	delete grassTexture;
}
