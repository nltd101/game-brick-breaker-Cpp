#include "pch.h"
#include "Heart.h"
Heart::Heart()
{
	font.loadFromFile("resources/zorque.ttf");
	this->heart.setFont(font);
	this->heart.setCharacterSize(55);
	//this->heart.setStyle(sf::Text::Bold);
	this->heart.setPosition(915, 140);
	this->heart.setFillColor(sf::Color(255, 0, 84));
}


Heart::~Heart()
{
}