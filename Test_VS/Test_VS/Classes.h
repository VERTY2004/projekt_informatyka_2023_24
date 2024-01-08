#ifndef CLASSES_HPP
#define CLASSES_HPP
#include "Classes.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Alien {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
public:
	float pozycjax();
	float pozycjay();
	void setTexture(const string& filePath);
	void setPosition(float x, float y);
	void draw(sf::RenderWindow& window);
	void move(float step, float jump);
	Alien();
};

class Spaceship {
private:
	float x_vel = 4, y_vel = 4;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	sf::Vector2f position;
	Spaceship(float x, float y);
	float pozycjax();
	float pozycjay();
	void przesun(float x_vel, float y_vel);
	void sterujx(int x, int x_size);
	void setScale(float scaleX, float scaleY);
	sf::Sprite getShip() const;
};

class Laser {
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	sf::Vector2f position;
	void fly(float speed, int frame);
	Laser();
	float pozycjax();
	float pozycjay();
	sf::Sprite getLaser() const;
	void teleport(float x, float y);
	void shoot(float x, float y, float speed);
	~Laser();
};
#endif 