#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include <ctime>
#include "Globalvars.h"

#include "Screen.h"
#include "SplashScreen.h"
#include "PauseScreen.h"
#include "MenuScreen.h"
#include "MapScreen.h"
#include "GameScreen.h"
#include "DeathScreen.h"
#include "LevelEndScreen.h"


//Used userDatas:
//player: 1
//playerFixture: 1001
//playerFootFixture: 1002
//levelGroundBody: 10
//levelGroundFixture: 1010
//enemyRange 11-100
//enemyFixtureRange 1011-1100
//ammoRange 101->
//ammoFixtureRange 1101->

//Global variables
const float SCALE = 30.f;
const float PI = 3.14159265f;
const short FRIENDLY_GROUP = -1;
const short HOSTILE_GROUP = -2;
const short GROUND_GROUP = -3;
const float TILESIZE = 50;
bool isPause = true;
bool isLevelEnd = false;

int main(int argc, char **argv)
{
	srand((unsigned int)time(NULL));

	//Application variables
	std::vector<Screen*> screens;
	int screen = 0;

	//Window creation
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML Demo 3");
	window.setFramerateLimit(80);

	//Mouse cursor no more visible
	window.setMouseCursorVisible(false);

	//Screen preparations
	SplashScreen splashScreen;
	MenuScreen menuScreen;
	MapScreen mapScreen;
	GameScreen gameScreen;
	PauseScreen pauseScreen;
	DeathScreen deathScreen;
	LevelEndScreen levelEndScreen;

	screens.push_back(&splashScreen);
	screens.push_back(&menuScreen);
	screens.push_back(&mapScreen);
	screens.push_back(&gameScreen);
	screens.push_back(&pauseScreen);
	screens.push_back(&deathScreen);
	screens.push_back(&levelEndScreen);

	//Main loop
	while (screen >= 0)
	{
		screen = screens[screen]->run(window);
	}

	return 0;
}