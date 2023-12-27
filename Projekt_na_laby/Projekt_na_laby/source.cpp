#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <SFML/Window/Keyboard.hpp>

using namespace std;

class Spaceship {
private:
	float x_vel = 4, y_vel = 4;  
	sf::Sprite sSprite;
	sf::Texture sTexture;
public:
	sf::Vector2f sPosition;
	Spaceship(float x, float y)
	{
		sPosition.x = x;
		sPosition.y = y;
		sTexture.loadFromFile("spaceship.png");
		sSprite.setTexture(sTexture);
		sSprite.setPosition(sPosition);
	}
	float pozycjax() {
		return sPosition.x;
	}
	float pozycjay() {
		return sPosition.y;
	}
	void przesun(float x_vel, float y_vel)
	{
		sf::Vector2f pos;
		pos.x = x_vel;
		pos.y = y_vel;
		sSprite.move(pos);
		sPosition = sSprite.getPosition();
	}
	void sterujx(int x, int x_size)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (sPosition.x == -40) {

			}
			else {
				przesun(-x, 0);
			}
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (sPosition.x == x_size-150) {
			
			}
			else {
				przesun(x, 0);
			}
		}
	}
	void setScale(float scaleX, float scaleY) {
		sSprite.setScale(scaleX, scaleY);
	}
	sf::Sprite getShip() const {
		return sSprite;
	}
};


/// <summary>
/// 
/// </summary>


class Enemy {
protected:
	sf::Sprite eSprite;
	sf::Vector2f ePosition;
	sf::Texture eTexture;
public:
	 Enemy(){
		eTexture.loadFromFile("Enemy1.png");
		eSprite.setTexture(eTexture);
		eSprite.setPosition(ePosition);
	} 

	 void ustaw_poz(float x, float y) {
		 ePosition.x = x;
		 ePosition.y = y;
		 eSprite.setPosition(ePosition);
	 }

	 void setScale(float scaleX, float scaleY) {
		 eSprite.setScale(scaleX, scaleY);
	 }

	sf::Sprite getEnemy() const {
		return eSprite;
	}
};


/// <summary>
/// 
/// </summary>


class Bullet {
private:
	sf::Sprite bSprite;
	sf::Texture bTexture;
public:
	sf::Vector2f bPosition;
	Bullet(float x, float y) {
		bPosition.x = x;
		bPosition.y = y;
		bTexture.loadFromFile("Bullet.png");
		bSprite.setTexture(bTexture);
		bSprite.setPosition(bPosition);
	}
	void pozycja(float x, float y) {
		bPosition.x = x;
		bPosition.y = y;
		bSprite.setPosition(bPosition);
	}

	void lot(float x,float y) {
		sf::Vector2f pos;
		pos.x = x;
		pos.y = y;
		bSprite.move(pos);
		bPosition = bSprite.getPosition();
	}

	sf::Sprite getBullet() const {
		return bSprite;
	}
};


int main()
{
	float x=1500;
	float y=1500;
	Spaceship ss1(x/2, y-200);
	Enemy en[10];
	Bullet pocisk(ss1.pozycjax(), ss1.pozycjay());
	chrono::microseconds interval(10);
	bool spacePressed = false;
	for (int i = 0;i < 10;i++) {
		en[i].setScale(0.1, 0.1);
		en[i].ustaw_poz(20+150*i, 50);
	}
	sf::RenderWindow window(sf::VideoMode(x, y), "Space Invaders");	
	sf::Event event;
	while (window.isOpen())	
	{
		// check all the window's events that were triggered since the last iteration of the loop
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (GetKeyState(VK_ESCAPE) & 0x8000)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space && !spacePressed) {
					spacePressed = true;
					cout << "spacebar was pressed\n";
					cout << "Pozycja statku to: " << ss1.pozycjax() << " " << ss1.pozycjay() << endl;
					pocisk.pozycja(ss1.pozycjax(), ss1.pozycjay());
					for (int i = 0;i < 100;i++) {
						pocisk.lot(0, -1);
						this_thread::sleep_for(interval);
						window.draw(pocisk.getBullet());
					}
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) {
					spacePressed = false;
				}
			}
		}

		ss1.setScale(0.7, 0.7);
		ss1.sterujx(1, x);

		window.clear(sf::Color::Black);
		window.draw(ss1.getShip());
		for (int i = 0;i < 10;i++) {
			window.draw(en[i].getEnemy());
		}
		window.draw(pocisk.getBullet()); 
		window.display();
	}
	return 0;
}