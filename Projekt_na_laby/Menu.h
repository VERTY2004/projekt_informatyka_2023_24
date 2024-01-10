#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#define Max_menu 3

class Menu {
public:
	Menu(float width, float height);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int menuPressed()
	{
		return menuSelected;
	}
	~Menu();
private:
	sf::Font font;
	sf::Text menu[Max_menu];
	int menuSelected;
};
