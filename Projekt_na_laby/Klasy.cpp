#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Klasy.h"

using namespace std;
using namespace sf;

Ship::Ship(float width, float height) {
	texture.loadFromFile("Spaceship.png");
	sprite.setTexture(texture);
	FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f); 
	sprite.setPosition(width/2,height-bounds.height/2);
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
void Ship::Steer(float width) {
	sf::Vector2f pos;
	pos.x = x_speed;
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		if(position.x>=44)
			sprite.move(-pos);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000) {
		if(position.x <= width-44)
			sprite.move(pos);
	}
	position = sprite.getPosition();
}

Alien::Alien() {

}
void Alien::setTexture(const string& filePath) {
	if (texture.loadFromFile(filePath)) 
		sprite.setTexture(texture);
	else
		cout << "An Error accurred while loading the texture" << endl;
}
void Alien::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}
float Alien::pozycja_x() {
	return position.x;
}
float Alien::pozycja_y() {
	return position.y;
}
void Alien::draw(sf::RenderWindow& window) { 
	window.draw(sprite);
}
void Alien::move(float step, float jump) {
	sf::Vector2f pos;
	pos.x = step;
	pos.y = jump;
	sprite.move(pos);
	position = sprite.getPosition();
}
FloatRect Alien::getBounds() {
	return sprite.getGlobalBounds();
}

Laser::Laser() {
	texture.loadFromFile("Bullet.png");
	sprite.setTexture(texture);
}
void Laser::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
void Laser::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}
void Laser::b_fly() {
	//sekcja if'ów zmieniaj¹cych wygl¹d pocisku w zale¿noœci od "frame"
	Vector2f pos;
	pos.y = -BSpeed;
	sprite.move(pos);
	position = sprite.getPosition();
}
float Laser::pozycja_y() {
	return position.y;
}
int Laser::kolizja(int al_amount, vector<Alien>aliens, float width) {
	for (int i = 0;i < al_amount;i++) {
		if (aliens[i].getBounds().contains(position))
			return i;
	}
	return -1;
}
Laser::~Laser() {

}
bool Laser::outOfBounds() {
	if (position.y <= -50)
		return true;
}
bool Laser::belowBounds(float height) {
	if (position.y >= height + 50)
		return true;
}

Pauza::Pauza(float width, float height, string text) {
	if (!font.loadFromFile("PublicPixel.ttf")) {
		cout << "Failed to load the font" << endl;
	}
	float char_size = 100;
	pauza.setFont(font);
	pauza.setFillColor(sf::Color::White);
	pauza.setString(text);
	pauza.setCharacterSize(char_size);
	sf::FloatRect bounds2 = pauza.getLocalBounds();
	pauza.setOrigin(bounds2.left + bounds2.width / 2.0f, bounds2.top + bounds2.height / 2.0f);
	pauza.setPosition(width / 2, height /2);
}
void Pauza::draw(RenderWindow& window) {
	window.draw(pauza);
}

Tracker::Tracker(float x, float y, string track, int value) {
	if (!font.loadFromFile("PublicPixel.ttf")) {
		cout << "Failed to load the font" << endl;
	}
	float char_size = 100;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setString(track+to_string(value));
	text.setCharacterSize(char_size);
	text.setPosition(x, y);
}
void Tracker::draw(RenderWindow& window) {
	window.draw(text);
}

void destroy(int indeks, vector<Alien>alien) {
	alien.erase(alien.begin() + indeks);
}