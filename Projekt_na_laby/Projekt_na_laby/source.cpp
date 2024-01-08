#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Windows.h> 
#include <iostream>
#include "Menu.h"
#include "Poziomy.h"

using namespace std;

int main()
{
	float width = 2736, height=1824;//wielkooœæ ekranu
	sf::RenderWindow window(sf::VideoMode(width, height), "Menu", sf::Style::Fullscreen);	
	sf::Event event;

	Menu menu(width, height);
	while (window.isOpen())	
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up) {
					menu.moveUp();
					break;
				}
				if (event.key.code == sf::Keyboard::Down) {
					menu.moveDown();
					break;
				}
				if (event.key.code == sf::Keyboard::Return) {
					int x = menu.menuPressed();
					if (x == 0) {
						cout << "Level 1 was pressed\n";
						level_1(width, height);
					}
					if (x == 1)
						cout << "Level 2 was pressed\n";
					if (x == 2) {
						cout << "Quit was pressed\n";
						window.close();
					}
				}
			}
		}
		window.clear(sf::Color::Black);
		menu.draw(window);
		window.display();
	}
	return 0;
}