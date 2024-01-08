#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Classes.h"

Laser::Laser() {
	texture.loadFromFile("Laser 1.png");
	sprite.setTexture(texture);
	sprite.setPosition(position);
}
float Laser::pozycjax() {
	return position.x;
}
float Laser::pozycjay() {
	return position.y;
}
void Laser::fly(float speed,int frame) {
	if (frame == 0) {
		texture.loadFromFile("Laser 1.png");
	}
	else if (frame == 1) {
		texture.loadFromFile("Laser 2.png");
	}
	else if (frame == 2) {
		texture.loadFromFile("Laser 3.png");
	}
	else if (frame >= 3) {
		texture.loadFromFile("Laser 4.png");
	}
	sf::Vector2f pos;
	pos.y = speed;
	sprite.move(pos);
	position = sprite.getPosition();
}
sf::Sprite Laser::getLaser() const {
	return sprite;
}

void Laser::teleport(float x, float y) {
	sf::Vector2f pos;
	pos.x = x;
	pos.y = y;
	sprite.setPosition(pos);
	position = sprite.getPosition();
}
void Laser::shoot(float x, float y, float speed) {
	texture.loadFromFile("Laser 1.png");
	sf::Vector2f pos;
	pos.y = speed;
	sprite.move(pos);
	position = sprite.getPosition();
}
Laser::~Laser() {

}