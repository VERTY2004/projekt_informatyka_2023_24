#include "Classes.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

	void Alien:: setTexture(const string& filePath) {
		if (texture.loadFromFile(filePath)) {
			sprite.setTexture(texture);
		}
		else {
			cout << "An Error accurred while loading the texture" << endl;
		}
	}
	void Alien::setPosition(float x, float y) {
		sprite.setPosition(x, y);
	}
	void Alien:: draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	float Alien::pozycjax() {
		return position.x;
	}
	float Alien::pozycjay() {
		return position.y;
	}
	void Alien::move(float step, float jump) {
		sf::Vector2f pos;
		pos.x = step;
		pos.y = jump;
		sprite.move(pos);
		position = sprite.getPosition();
	}
	Alien::Alien() {
	}
