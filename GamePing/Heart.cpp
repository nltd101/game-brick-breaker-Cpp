#include "pch.h"
#include "Heart.h"
Heart::Heart()
{
	font.loadFromFile("resources/Font.ttf");
	this->heart.setFont(font);
	this->heart.setCharacterSize(50);
	this->heart.setPosition(500.f, 350.f);
	this->heart.setFillColor(sf::Color::Red);
}


Heart::~Heart()
{
}