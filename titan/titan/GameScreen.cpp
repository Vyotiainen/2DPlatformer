#include "GameScreen.h"

const sf::Time GameScreen::TimePerFrame = sf::seconds(1.f / 60.f);

GameScreen::GameScreen()
{

}

int GameScreen::run(sf::RenderWindow &window){
	bool running = true;
	int isEnd = -1;

	if (isPause){
		isPause = false;
		_gameState.hardReset();
	}

	isLevelEnd = false;

	sf::Clock clock;
	sf::Time dt = sf::Time::Zero;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	window.setMouseCursorVisible(false);
	while (running){
		sf::Event event;

		dt = clock.restart();
		timeSinceLastUpdate += dt;
		timeSinceLastUpdate -= TimePerFrame;

		//Verifying events
		while (window.pollEvent(event)){
			// Window closed
			if (event.type == sf::Event::Closed){
				return -1;
			}

			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Escape){
					return PAUSE;
				}
			}
		}

		//Clearing screen
		window.clear(sf::Color::White);

		//Update box2d world
		isEnd = _gameState.update();

		//Drawing
		_gameState.draw(window);

		//Display
		window.display();

		switch (isEnd)
		{
		case 1:
			_gameState.softReset();
			return DEATH;
			break;
		case 2:
			_gameState.softReset();
			return END;
			break;
		}
	}

	//Never reaching this point normally
	return (-1);
}

GameScreen::~GameScreen()
{

}
