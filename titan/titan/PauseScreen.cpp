#include "PauseScreen.h"
#include <iostream>

PauseScreen::PauseScreen()
{
}

int PauseScreen::run(sf::RenderWindow &window){
	window.setView(window.getDefaultView());
	sf::Event event;
	bool running = true;
	sf::Sprite sprite;
	int alpha = 0;
	sf::Font font;
	sf::Text menu1;
	sf::Text menu2;
	sf::Text menu3;

	int menu = 0;

	sprite.setColor(sf::Color(255, 255, 255));
	if (!font.loadFromFile("verdanab.ttf"))
	{
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}

	menu1.setFont(font);
	menu1.setCharacterSize(20);
	menu1.setString("Back to game");
	menu1.setPosition({ 280.f, 160.f });

	menu2.setFont(font);
	menu2.setCharacterSize(20);
	menu2.setString("Options");
	menu2.setPosition({ 280.f, 220.f });

	menu3.setFont(font);
	menu3.setCharacterSize(20);
	menu3.setString("Exit");
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

			//Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (menu > 0) {
						menu--;
					}
					else if (menu == 0){
						menu = 2;
					}
					break;
				case sf::Keyboard::Down:
					if (menu < 2) {
						menu++;
					}
					else if (menu == 2){
						menu = 0;
					}
					break;
				case sf::Keyboard::Return:
					if (menu == 0){
						return GAME;
					}
					else if (menu == 1) {
						return PAUSE;
					}
					else {
						return MENU;
					}
					break;
				case sf::Keyboard::Escape:
					return GAME;
					break;
				default:
					break;
				}
			}
		}

		if (menu == 0){
			menu1.setColor(sf::Color(255, 0, 0, 255));
			menu2.setColor(sf::Color(255, 255, 255, 255));
			menu3.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (menu == 1){
			menu1.setColor(sf::Color(255, 255, 255, 255));
			menu2.setColor(sf::Color(255, 0, 0, 255));
			menu3.setColor(sf::Color(255, 255, 255, 255));
		}
		else{
			menu1.setColor(sf::Color(255, 255, 255, 255));
			menu2.setColor(sf::Color(255, 255, 255, 255));
			menu3.setColor(sf::Color(255, 0, 0, 255));
		}

		//Clearing screen
		window.clear();

		//Drawing
		window.draw(sprite);

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		//Display
		window.display();
	}

	//Never reaching this point normally
	return -1;
}

PauseScreen::~PauseScreen()
{
}
