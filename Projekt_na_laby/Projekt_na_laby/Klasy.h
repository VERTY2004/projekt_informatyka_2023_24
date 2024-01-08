#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Ship {
private:
	float x_speed = 4;
	Texture texture;
	Sprite sprite;
	Vector2f position;
public:
	Ship(float width, float height);
	float pozycja_x();
	float pozycja_y();
	void draw(RenderWindow& window);
};
