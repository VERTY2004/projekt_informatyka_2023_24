#include "Poziomy.h"
#include "Klasy.h"
#include <iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void level_1(float width, float height) 
{
	RenderWindow window(VideoMode(width, height), "Level 1", Style::Fullscreen);
	Event event;
	Ship ship(width, height);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}
		window.clear(sf::Color::Black);
		ship.draw(window);
		window.display();
	}
}