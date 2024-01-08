#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Classes.h"

Spaceship::Spaceship(float x, float y)
{
	position.x = x;
	position.y = y;
	texture.loadFromFile("spaceship.png");
	sprite.setTexture(texture);
	sprite.setPosition(position);
}
float Spaceship::pozycjax() {
	return position.x;
}
float Spaceship::pozycjay() {
	return position.y;
}
void Spaceship::przesun(float x_vel, float y_vel)
{
	sf::Vector2f pos;
	pos.x = x_vel;
	pos.y = y_vel;
	sprite.move(pos);
	position = sprite.getPosition();
}
void Spaceship::sterujx(int x, int x_size)
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		if (position.x <= 0) {

		}
		else {
			przesun(-x, 0);
		}
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		if (position.x >= x_size - 150) {

		}
		else {
			przesun(x, 0);
		}
	}
}
void Spaceship::setScale(float scaleX, float scaleY) {
	sprite.setScale(scaleX, scaleY);
}
sf::Sprite Spaceship::getShip() const {
	return sprite;
}