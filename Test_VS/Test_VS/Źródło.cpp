#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Classes.h"

using namespace std;

int main()
{
	int score = 0, lives=3,ruch=3, frame=0, Lframe=0;//"frame"-do ruchu kosmitów, "Lframe"-do ruchu laserów
	const int amount = 10, bamount = 5; int bnr = 0;//"bnr"=bullet nurmber
	int current_amount = 3 * amount; // powinno byæ "3 * amount"
	float screenWidth = GetSystemMetrics(SM_CXSCREEN), screenHeight = GetSystemMetrics(SM_CYSCREEN); // pobranie wymiarów ekranu, mo¿liwie niepotrzebne
	float distance = screenWidth/9, step=30, jump=90;
	sf::RenderWindow window(sf::VideoMode(screenHeight*2, screenHeight*1.5), "Inwazja Kosmitów"); 
	sf::Font font;
	sf::Event event;
	sf::Clock clock; sf::Clock cd_timer; sf::Clock hp_timer;
	sf::Time elapsed; sf::Time cooldown = sf::milliseconds(300); sf::Time hp_cd = sf::milliseconds(500);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 100);
	const int probability = 5;
	Alien al1[amount];
	Alien al2[amount];
	Alien al3[amount];
	int l1[amount] = { 0 }, l2[amount] = { 0 }, l3[amount] = { 0 };
	const int maxl = 3;
	Laser laser1[amount][maxl];
	Laser laser2[amount][maxl];
	Laser laser3[amount][maxl];
	Laser bullet[bamount];
	for (int n = 0;n < maxl;n++) {
		for (int i = 0;i < amount;i++) {
			laser1[i][n].teleport(0, 2000);
		}
		for (int i = 0;i < amount;i++) {
			laser2[i][n].teleport(0, 2000);
		}
		for (int i = 0;i < amount;i++) {
			laser3[i][n].teleport(0, 2000);
		}
	}
	Spaceship ship(screenHeight-100,screenHeight*1.5-160);
	cout << "screen Height = "<<screenHeight<<endl<<"screen Width = "<< screenWidth<<endl;
	for (int i = 0;i < amount;i++) {
		al1[i].setPosition(87 + i * distance, 100);
		al2[i].setPosition(80+ i * distance, 200);
		al3[i].setPosition(100 + i * distance, 300);
	}
	if (!font.loadFromFile("PublicPixel.ttf"))
	{
		cout << "Failed do load the font!";
	}
	window.setFramerateLimit(50);
	while (window.isOpen()) 
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				sf::Time elapsed = cd_timer.getElapsedTime();
				if (elapsed > cooldown) {
					bullet[bnr].teleport(ship.pozycjax() + 60, ship.pozycjay());
					bnr += 1;
					
					if (bnr >= bamount) {
						bnr = 0;
					}
				cd_timer.restart();
				}
			}
		}
		elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() >= 0.05+0.03*current_amount) {
			if (frame == 0) {
				for (int i = 0;i < amount;i++) {
					al1[i].setTexture("Alien 1.png");
					al2[i].setTexture("Alien 2.png");
					al3[i].setTexture("Alien 3.png");
					frame = 1;
				}
			}
			else if (frame == 1) {
				for (int i = 0;i < amount;i++) {
					al1[i].setTexture("Alien 1M.png");
					al2[i].setTexture("Alien 2M.png");
					al3[i].setTexture("Alien 3M.png");
					frame = 0;
				}
			}
			if (ruch >= 11) {
				step *= -1;
				ruch = 0;
				for (int i = 0;i < amount;i++) {
					al1[i].move(0, jump);
					al2[i].move(0, jump);
					al3[i].move(0, jump);
				}
			}
			else {
				for (int i = 0;i < amount;i++) {
					al1[i].move(step, 0);
					al2[i].move(step, 0);
					al3[i].move(step, 0);
				}
			}
			for (int i = 0;i < amount;i++) {
				int randomValue = dis(gen);
				if (randomValue <= probability) {
					laser1[i][l1[i]].teleport(al1[i].pozycjax(), al1[i].pozycjay());
					l1[i] += 1;
				}
				if (l1[i] >= maxl) {
					l1[i] = 0;
				}
			}
			for (int i = 0;i < amount;i++) {
				int randomValue = dis(gen);
				if (randomValue <= probability) {
					laser2[i][l2[i]].teleport(al2[i].pozycjax(), al2[i].pozycjay());
					l2[i] += 1;
				}
				if (l2[i] >= maxl) {
					l2[i] = 0;
				}
			}
			for (int i = 0;i < amount;i++) {
				int randomValue = dis(gen);
				if (randomValue <= probability) {
					laser3[i][l3[i]].teleport(al3[i].pozycjax(), al3[i].pozycjay());
					l3[i] += 1;
				}
				if (l3[i] >= maxl) {
					l3[i] = 0;
				}
			}
			ruch++;
			clock.restart();
		}

		for (int n = 0;n < maxl;n++) {
			sf::Time elapsed = hp_timer.getElapsedTime();
			for (int i = 0;i < amount;i++) {
				if (laser1[i][n].pozycjax() >= ship.pozycjax() - 15
					and laser1[i][n].pozycjax() <= ship.pozycjax() + 90
					and laser1[i][n].pozycjay() >= ship.pozycjay() - 15
					and laser1[i][n].pozycjay() <= ship.pozycjay() + 90
					and elapsed >= hp_cd) {
					lives -= 1;
					hp_timer.restart();
				}
				if (laser2[i][n].pozycjax() >= ship.pozycjax() - 15
					and laser2[i][n].pozycjax() <= ship.pozycjax() + 90
					and laser2[i][n].pozycjay() >= ship.pozycjay() - 15
					and laser2[i][n].pozycjay() <= ship.pozycjay() + 90
					and elapsed >= hp_cd) {
					lives -= 1;
					hp_timer.restart();
				}
				if (laser3[i][n].pozycjax() >= ship.pozycjax() - 15
					and laser3[i][n].pozycjax() <= ship.pozycjax() + 90
					and laser3[i][n].pozycjay() >= ship.pozycjay() - 15
					and laser3[i][n].pozycjay() <= ship.pozycjay() + 90
					and elapsed >= hp_cd) {
					lives -= 1;
					hp_timer.restart();
				}
			}
		}
		for (int i = 0;i < bamount;i++) {
			bullet[i].fly(-32, Lframe);
		}
		for (int n = 0;n < maxl;n++) {
			for (int i = 0;i < amount;i++) {
				laser1[i][n].fly(10, Lframe);
				laser2[i][n].fly(10, Lframe);
				laser3[i][n].fly(10, Lframe);
			}
		}
		Lframe++;
		if (Lframe >= 4) {
			Lframe = 0;
		}
		for (int i = 0;i < bamount;i++) {
			for (int n = 0;n < amount;n++) {
				if (bullet[i].pozycjax() >= al1[n].pozycjax()-15 
					and bullet[i].pozycjax() <= al1[n].pozycjax()+70
					and bullet[i].pozycjay() >= al1[n].pozycjay() - 15
					and bullet[i].pozycjay() <= al1[n].pozycjay() + 40) {
					score += 150;
					current_amount -= 1;
					al1[n].move(0, 2000);
					bullet[i].teleport(0, -100);
				}
				if (bullet[i].pozycjax() >= al2[n].pozycjax() - 20
					and bullet[i].pozycjax() <= al2[n].pozycjax() + 75
					and bullet[i].pozycjay() >= al2[n].pozycjay() - 15
					and bullet[i].pozycjay() <= al2[n].pozycjay() + 40) {
					score += 100;
					current_amount -= 1;
					al2[n].move(0, 2000);
					bullet[i].teleport(0, -100);
				}
				if (bullet[i].pozycjax() >= al3[n].pozycjax() - 15
					and bullet[i].pozycjax() <= al3[n].pozycjax() + 70
					and bullet[i].pozycjay() >= al3[n].pozycjay() - 15
					and bullet[i].pozycjay() <= al3[n].pozycjay() + 40) {
					score += 50;
					current_amount -= 1;
					al3[n].move(0, 2000);
					bullet[i].teleport(0, -100);
				}
			}
		}
		sf::Text text("Score:" + to_string(score), font, 70);
		text.setPosition(50, 10);
		sf::Text lives_text("HP: " + to_string(lives), font, 70);
		lives_text.setPosition(1200, 10);
		ship.sterujx(20, screenHeight * 2);
		window.clear();
		window.draw(text);
		window.draw(lives_text);
		if (score >= 3000) {
			sf::Text victory_text("YOU WIN!", font, 70);
			victory_text.setPosition(630, 600);
			window.draw(victory_text);
		}
		for(int i=0;i<amount;i++){
			if (al1[i].pozycjay() >= 1100 and al1[i].pozycjay() <= 1500) {
				sf::Text lose_text("YOU LOSE!", font, 70);
				lose_text.setPosition(630, 600);
				window.draw(lose_text);
			}
			if (al2[i].pozycjay() >= 1200 and al2[i].pozycjay() <= 1500) {
				sf::Text lose_text("YOU LOSE!", font, 70); 
				lose_text.setPosition(630, 600); 
				window.draw(lose_text); 
			}
			if (al3[i].pozycjay() >= 1100 and al3[i].pozycjay() <= 1500) {
				sf::Text lose_text("YOU LOSE!", font, 70); 
				lose_text.setPosition(630, 600); 
				window.draw(lose_text); 
			}
		}
		if (lives <= 0) {
			sf::Text lose_text("YOU LOSE!", font, 70);
			sf::Text final_score("Final score:" + to_string(score), font, 70);
			final_score.setPosition(430, 700);
			lose_text.setPosition(630, 600);
			window.draw(final_score);
			window.draw(lose_text);
			for (int i = 0;i < amount;i++) {
				al1[i].move(0, 2000);
				al2[i].move(0, 2000);
				al3[i].move(0, 2000);
			}
			for (int n = 0;n < maxl;n++) {
				for (int i = 0;i < amount;i++) {
					laser1[i][n].teleport(-100, 0);
					laser2[i][n].teleport(-100, 0);
					laser3[i][n].teleport(-100, 0);
				}
			}
		}
		for (int n = 0;n < maxl;n++) {
			for (int i = 0;i < amount;i++) {
				if (laser1[i][n].pozycjay() <= 2000) {
					window.draw(laser1[i][n].getLaser());
				}
				if (laser2[i][n].pozycjay() <= 2000) {
					window.draw(laser2[i][n].getLaser());
				}
				if (laser3[i][n].pozycjay() <= 2000) {
					window.draw(laser3[i][n].getLaser());
				}
			}
		}
		for (int i = 0;i < bamount;i++) {
			window.draw(bullet[i].getLaser());
		}
		window.draw(ship.getShip());
		for (int i = 0;i < amount;i++) {
			if (al1[i].pozycjay() <= 2000) {
				al1[i].draw(window);
			}
			if (al2[i].pozycjay() <= 2000) {
				al2[i].draw(window);
			}
			if (al3[i].pozycjay() <= 2000) {
				al3[i].draw(window);
			}
		}
		window.display();
	}
	cout << "Final Score: " << score << endl;
	return 0;
}