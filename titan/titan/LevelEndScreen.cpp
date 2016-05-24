#include "LevelEndScreen.h"
#include "Globalvars.h"
#include <iostream>

LevelEndScreen::LevelEndScreen()
{
}

int LevelEndScreen::run(sf::RenderWindow &window){
	window.setView(window.getDefaultView());
	sf::Event event;
	bool running = true;

	sf::Font font;
	sf::Text menu1;
	sf::Text menu2;
	sf::Text menu3;

	if (!font.loadFromFile("verdanab.ttf"))
	{
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}

	menu1.setFont(font);
	menu1.setCharacterSize(30);
	menu1.setString("Level completed");
	menu1.setPosition({ 280.f, 160.f });

	menu2.setFont(font);
	menu2.setCharacterSize(30);
	menu2.setString("Score");
	menu2.setPosition({ 280.f, 220.f });

	menu3.setFont(font);
	menu3.setCharacterSize(20);
	menu3.setString("Press Enter to Continue");
	menu3.setPosition({ 280.f, 280.f });

	window.setKeyRepeatEnabled(false);
	while (running)
	{
		//Verifying events
		while (window.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				return -1;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
			isLevelEnd = true;
			isPause = false;
			return MAP;
		}

		//Clearing screen
		window.clear();

		//Drawing
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		//Display
		window.display();
	}

	//Never reaching this point normally
	return -1;
}


LevelEndScreen::~LevelEndScreen()
{
}
