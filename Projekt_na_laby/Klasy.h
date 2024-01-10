#ifndef KLASY_H
#define KLASY_H
#include <iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Ship {
private:
	float x_speed = 15;
	Texture texture;
	Sprite sprite;
	Vector2f position;
public:
	Ship(float width, float height);
	float pozycja_x();
	float pozycja_y();
	void draw(RenderWindow& window);
	void Steer(float width);
};

class Alien {
private:
	Texture texture;
	Sprite sprite;
	Vector2f position;
public:
	Alien();
	void setTexture(const string& filePath);
	float pozycja_x();
	float pozycja_y();
	void draw(RenderWindow& window);
	void setPosition(float x, float y);
	void move(float step, float jump);
	FloatRect getBounds();
	//bool hit(Vector2f BPosition int& indeks);
};

class Laser {
private:
	Sprite sprite;
	Texture texture;
	Vector2f position;
	float speed = 5;
	float BSpeed = 40;
public:
	Laser();
	void setPosition(float x, float y);
	void b_fly();
	void draw(RenderWindow& window);
	float pozycja_y();
	bool outOfBounds();
	bool belowBounds(float height);
	int kolizja(int indeks, vector<Alien>aliens, float width);
	~Laser();
};

class Pauza {
public:
	Pauza(float width, float height, string text);
	void draw(RenderWindow& window);
private:
	sf::Font font;
	sf::Text pauza;
};

class Tracker {
public:
	Tracker(float x, float y, string track, int value);
	void draw(RenderWindow& window);
private:
	Font font;
	Text text;
};

void destroy(int indeks, vector<Alien>alien);
#endif