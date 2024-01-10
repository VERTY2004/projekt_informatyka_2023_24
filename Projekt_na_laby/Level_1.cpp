#include "Poziomy.h"
#include "Klasy.h"
#include <iostream>
#include<SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

void level_1(float width, float height) //width = 2736, height=1824
{
	
	int al_amount = 10, s_amount = 0, step = 88, jump = 128, score=0;
	bool frame = false, border = false, pause =false, hit = false;
	RenderWindow window(VideoMode(width, height), "Level 1", Style::Fullscreen);
	window.setFramerateLimit(60);
	Event event;
	Time elapsed;
	Clock clock, cooldown;
	Ship ship(width, height);
	vector<Alien>al1;
	vector<Laser>s_laser;
	Laser bullet;
	Pauza pauza(width, height, "PAUSE"), victory(width, height, "VICTORY!");
	for (int i = 0;i < al_amount;i++) {
		al1.push_back(Alien());
		al1[i].setPosition(576+176*i, 100);//Alien 1.png(width =88, height = 64) set up: "once every 2 lengths"
	}
	for (int i = 0;i < al1.size();i++) {
		al1[i].setTexture("Alien 1.png");
	}
	while (window.isOpen())
	{
		if (pause == false or al_amount > 0) {
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (Keyboard::isKeyPressed(Keyboard::Escape))
					window.close();
				if (Keyboard::isKeyPressed(Keyboard::P) and al_amount > 0)
					pause = true;
				if (event.type == sf::Event::KeyReleased) {
					if (event.key.code == Keyboard::Space) {
						elapsed = cooldown.getElapsedTime();
						if (elapsed.asSeconds() >= 0.4) {
							//stworzenia lasera na pozycji statku
							s_laser.push_back(bullet);
							s_laser[s_amount].setPosition(ship.pozycja_x(), ship.pozycja_y());
							s_amount++;
							cooldown.restart();
						}
					}
				}
			}
			elapsed = clock.getElapsedTime();
			if (al_amount > 0) {
				if (elapsed.asSeconds() >= 0.1 + 0.04*al_amount) {
					if ((al1[al_amount - 1].pozycja_x() >= width - 176 or al1[0].pozycja_x() <= 88) and border == false) {
						border = true;
						step = -step;
					}
					else {
						border = false;
					}
					if (border == false) {
						if (frame == false) {
							for (int i = 0;i < al_amount;i++) {
								//zmieñ wygl¹d na 1
								al1[i].setTexture("Alien 1.png");
								al1[i].move(step, 0);
							}
						}
						if (frame == true) {
							for (int i = 0;i < al_amount;i++) {
								//zmieñ wygl¹d na 2
								al1[i].setTexture("Alien 1M.png");
								al1[i].move(step, 0);
							}
						}
					}
					else if (border == true) {
						if (frame == false) {
							for (int i = 0;i < al_amount;i++) {
								//zmieñ wygl¹d na 1
								al1[i].move(0, jump);
							}
						}
						if (frame == true) {
							for (int i = 0;i < al_amount;i++) {
								//zmieñ wygl¹d na 2
								al1[i].move(0, jump);
							}
						}
					}
					frame = !frame;
					clock.restart();
				}
			}
			for (int i = 0;i < s_laser.size();i++) {
				s_laser[i].b_fly();
			}
			for (int i = 0;i < s_laser.size();i++) { //usuñ pociski po wyjœciu poza ekran
				if (s_laser[i].outOfBounds() == true) {
					s_laser.erase(s_laser.begin());
					s_amount--;
				}
			}
			for (int i = 0;i < s_amount;i++) {//usuñ kosmitów i pociski po trafieniu
				int trafiony = s_laser[i].kolizja(al_amount, al1, 64);
				if (trafiony > -1) {
					s_laser.erase(s_laser.begin()+i);
					s_amount--;
					al1.erase(al1.begin() + trafiony);
					al_amount--;
					cout << "trafiony\n";
					hit = true;
					score += 50;
				}
			}
			if (hit == true) {//update texture after erasing an alien
				for (int i = 0;i < al_amount;i++) {
					if (frame == false) {
						al1[i].setTexture("Alien 1M.png");
					}
					else {
						al1[i].setTexture("Alien 1.png");
					}
				}
				hit = false;
			}
			ship.Steer(width);
		}
		if (pause == true) {
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (Keyboard::isKeyPressed(Keyboard::Escape))
					window.close();
				if (Keyboard::isKeyPressed(Keyboard::P))
					pause = false;
			}
		}
		window.clear(sf::Color::Black);
		for (int i = 0;i<al_amount;i++) {
			al1[i].draw(window);
		}
		for (int i = 0;i < s_laser.size();i++) {
			s_laser[i].draw(window);
		}
		ship.draw(window);
		Tracker score_text(50, 50, "SCORE: ", score);
		score_text.draw(window);
		if (pause == true)
			pauza.draw(window);
		if (al_amount == 0)
			victory.draw(window);
		window.display();
	}
}