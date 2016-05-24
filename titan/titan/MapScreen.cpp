#include "MapScreen.h"
#include "Globalvars.h"
#include <iostream>


MapScreen::MapScreen()
{
}

int MapScreen::run(sf::RenderWindow &window){
	window.setView(window.getDefaultView());
	sf::Event event;

	if (!isLevelEnd){
		isPause = true;
	}

	bool running = true;
	bool selected = false;

	sf::RectangleShape tempBackground;
	tempBackground.setFillColor(sf::Color::White);
	tempBackground.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));

	sf::RectangleShape levels[5];
	sf::CircleShape hover;

	hover.setRadius(30);
	hover.setFillColor(sf::Color(255, 255, 0));

	for (int i = 0; i < 5; i++){
		levels[i].setFillColor(sf::Color(192, 192, 192));
		levels[i].setSize(sf::Vector2f(20, 20));
		levels[i].setOrigin(sf::Vector2f(10, 10));
		levels[i].setOutlineThickness(-2);
		levels[i].setOutlineColor(sf::Color::Black);
	}

	levels[0].setFillColor(sf::Color::Green);

	levels[0].setPosition(100, 100);
	levels[1].setPosition(300, 424);
	levels[2].setPosition(664, 123);
	levels[3].setPosition(400, 240);
	levels[4].setPosition(700, 450);

	sf::Texture mapBackground;
	if (!mapBackground.loadFromFile("presentation.jpg"))
	{
		std::cerr << "Error loading presentation.jpg" << std::endl;
		return (-1);
	}

	sf::Font font;
	if (!font.loadFromFile("verdanab.ttf"))
	{
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}

	window.setMouseCursorVisible(true);
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

		if (sf::Mouse::getPosition(window).x <= levels[0].getPosition().x + 10 &&
			sf::Mouse::getPosition(window).x >= levels[0].getPosition().x - 10 &&
			sf::Mouse::getPosition(window).y <= levels[0].getPosition().y + 10 &&
			sf::Mouse::getPosition(window).y >= levels[0].getPosition().y - 10){
			levels[0].setSize(sf::Vector2f(30, 30));
			selected = true;
			hover.setPosition(sf::Vector2f(levels[0].getPosition().x - 25, levels[0].getPosition().y - 25));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				return GAME;
			}

		}
		else {
			selected = false;
			levels[0].setSize(sf::Vector2f(20, 20));
		}

		//Clearing screen
		window.clear();

		//Drawing
		window.draw(tempBackground);

		if (selected){
			window.draw(hover);
		}

		for (int i = 0; i < 5; i++){
			window.draw(levels[i]);
		}

		//Display
		window.display();
	}

	//Never reaching this point normally
	return -1;
}

MapScreen::~MapScreen()
{
}
