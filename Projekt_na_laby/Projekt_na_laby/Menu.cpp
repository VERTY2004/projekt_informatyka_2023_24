#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("PublicPixel.ttf")) {
		cout << "Failed to load the font" << endl;
	}
	float char_size = 80;

	//Level 1
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("Level 1");
	menu[0].setCharacterSize(char_size);
	sf::FloatRect bounds0 = menu[0].getLocalBounds();
	menu[0].setOrigin(bounds0.left + bounds0.width / 2.0f, bounds0.top + bounds0.height / 2.0f);
	menu[0].setPosition(width / 2, 1 * height / 5);

	//Level 2
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Level 2");
	menu[1].setCharacterSize(char_size);
	sf::FloatRect bounds1 = menu[1].getLocalBounds();
	menu[1].setOrigin(bounds1.left + bounds1.width / 2.0f, bounds1.top + bounds1.height / 2.0f);
	menu[1].setPosition(width / 2, 2 * height / 5);

	//Quit
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Quit");
	menu[2].setCharacterSize(char_size);
	sf::FloatRect bounds2 = menu[2].getLocalBounds();
	menu[2].setOrigin(bounds2.left + bounds2.width / 2.0f, bounds2.top + bounds2.height / 2.0f);
	menu[2].setPosition(width / 2, 3 * height / 5);

	menuSelected = 0;
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0;i < 3;i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (menuSelected - 1 >= -1)
	{
		menu[menuSelected].setFillColor(sf::Color::White);
		menuSelected--;
		if (menuSelected == 3)
		{
			menuSelected = 0;
		}
		menu[menuSelected].setFillColor(sf::Color::Blue);
	}
}

void Menu::moveDown()
{
	if (menuSelected + 1 <= Max_menu)
	{
		menu[menuSelected].setFillColor(sf::Color::White);
		menuSelected++;
		if (menuSelected == 3)
		{
			menuSelected = 0;
		}
		menu[menuSelected].setFillColor(sf::Color::Blue);
	}
}

Menu::~Menu() {
	printf("End of the Game\n");
}

