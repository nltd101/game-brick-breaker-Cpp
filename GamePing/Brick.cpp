#include "pch.h"
#include "Brick.h"

Brick::Brick()
{
	BRICK.setSize(brickSize);
	BRICK.setOutlineThickness(2);
	BRICK.setOutlineColor(sf::Color(238, 232, 170));
	//BRICK.setOutlineColor(sf::Color::White);
	//BRICK.setFillColor(sf::Color(r, g, b));
	BRICK.setOrigin(brickSize / 2.f);
}
