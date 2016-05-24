#include "GameState.h"
#include "Globalvars.h"
#include <iostream>
#include <list>
#include "Player.h"
#include "FirstLevel.h"


GameState::GameState()
{
	hardInit();
}

//Initialize current gamestate
void GameState::hardInit(){

	/** Prepare the world */
	b2Vec2 gravity(0.f, 9.8f);
	_world = new b2World(gravity);
	_world->SetContactListener(&_listener);

	_view = new sf::View(sf::FloatRect(0, 0, 800, 600));

	_player = new Player(1, _world);

	_currentLevel = new FirstLevel(_world, _player);
}

void GameState::softInit(){

	/** Prepare the world */
	b2Vec2 gravity(0.f, 9.8f);
	_world = new b2World(gravity);
	_world->SetContactListener(&_listener);

	_view = new sf::View(sf::FloatRect(0, 0, 800, 600));

	_player->setBody(1, _world);

	_currentLevel = new FirstLevel(_world, _player);
}


void GameState::draw(sf::RenderWindow &window){
	window.setView(*_view);

	_currentLevel->draw(window);

	_player->draw(window);

	_view->reset(sf::FloatRect(SCALE * _player->getBody()->GetPosition().x + -400, SCALE * _player->getBody()->GetPosition().y - 500, 1000, 800));

	updateHUD(window);
}

int GameState::update(){
	_world->Step(1 / 60.f, 8, 3);
	_world->ClearForces();

	_player->processInput(_world);

	_currentLevel->update(_world, b2Vec2(_player->getBody()->GetPosition().x / SCALE, _player->getBody()->GetPosition().y / SCALE));

	checkContacts();

	if (_player->getHp() <= 0){
		return 1;
	}

	if (_player->getEnd() <= _player->getBody()->GetPosition().x){
		return 2;
	}

	return -1;
}

void GameState::checkContacts(){
	if (!_listener.getDeleteList()->empty()){
		_listener.getDeleteList()->unique();
		for (std::list<Drawable*>::iterator it = _listener.getDeleteList()->begin(); it != _listener.getDeleteList()->end(); it++){

			if (((Drawable*)*it)->returnID() == NORMALENEMY) {
				_player->gainExp(100);
			}

			((Drawable*)*it)->deleteBody();
			delete *it;
		}
		_listener.getDeleteList()->clear();
	}
}

void GameState::updateHUD(sf::RenderWindow &window) {
	window.setView(window.getDefaultView());

	sf::RectangleShape barFrame;
	barFrame.setSize(sf::Vector2f(100 * 2, 10 * 2));
	barFrame.setFillColor(sf::Color::Transparent);
	barFrame.setOutlineThickness(3);
	barFrame.setOutlineColor(sf::Color::Black);
	barFrame.setPosition(50, 50);

	sf::RectangleShape hpBar;
	hpBar.setSize(sf::Vector2f((_player->getCurHP() * 100 * 2), 10 * 2));
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setPosition(50, 50);

	window.draw(barFrame);
	window.draw(hpBar);

	barFrame.setOrigin(100, 0);
	barFrame.setPosition((window.getSize().x - 150.f), 50.f);

	sf::RectangleShape expBar;
	expBar.setOrigin(-100, 0);
	expBar.setSize(sf::Vector2f(-(_player->getExp() * 100 * 2), 10 * 2));
	expBar.setFillColor(sf::Color::Green);
	expBar.setPosition((window.getSize().x - 150.f), 50.f);

	window.draw(barFrame);
	window.draw(expBar);

	window.setView(*_view);
}

void GameState::hardReset(){
	hardResetDelete();
	hardInit();
}

void GameState::softReset(){
	softResetDelete();
	softInit();
	_player->setHp(_player->getMaxHP());
}

void GameState::softResetDelete(){
	delete _world;
	delete _currentLevel;
	delete _view;
}

void GameState::hardResetDelete(){
	delete _world;
	delete _currentLevel;
	delete _player;
	delete _view;
}

GameState::~GameState()
{
	delete _world;
	delete _currentLevel;
	delete _player;
	delete _view;
}
