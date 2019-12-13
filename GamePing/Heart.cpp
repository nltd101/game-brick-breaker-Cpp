#include "pch.h"
#include "Heart.h"
Heart::Heart()
{
	font.loadFromFile("resources/Font.ttf");
	this->heart.setFont(font);
	this->heart.setCharacterSize(60);
	this->heart.setStyle(sf::Text::Bold);
	this->heart.setPosition(920, 90);
	this->heart.setFillColor(sf::Color::Red);
}


Heart::~Heart()
{
}