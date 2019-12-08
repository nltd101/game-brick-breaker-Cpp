#include "pch.h"
#include "ScoreNow.h"


ScoreNow::ScoreNow()
{
	font.loadFromFile("resources/Font.ttf");
	this->scoreNow.setFont(font);
	this->scoreNow.setCharacterSize(50);
	this->scoreNow.setPosition(10.f, 350.f);
	this->scoreNow.setFillColor(sf::Color::Red);
}


ScoreNow::~ScoreNow()
{
}