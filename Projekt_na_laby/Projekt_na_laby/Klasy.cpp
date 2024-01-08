#include <iostream>
#include <SFML/Graphics.hpp>
#include "Klasy.h"

using namespace std;
using namespace sf;

Ship::Ship(float width, float height) {
	texture.loadFromFile("Spaceship.png");
	sprite.setTexture(texture);
	FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	sprite.setPosition(width/2,height/5);
}
float Ship::pozycja_x() {
	return position.x;
}
float Ship::pozycja_y() {
	return position.y;
}
void Ship::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

