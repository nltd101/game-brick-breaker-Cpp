#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <list>
using namespace std;
class SaveTraceBall
{
private:
	float ballRadius = 15.f;
public:
	list<sf::CircleShape*> listSprite;
	void newMove(int ,int, sf::RenderWindow &mwindow);
	void drawShadow(sf::RenderWindow &mwindow);
};

