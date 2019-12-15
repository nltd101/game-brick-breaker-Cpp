#include "pch.h"
#include "ScoreNow.h"


ScoreNow::ScoreNow()
{
	font.loadFromFile("resources/zorque.ttf");
	this->scoreNow.setFont(font);
	this->scoreNow.setCharacterSize(50);
	this->scoreNow.setPosition(895, 235);
	this->scoreNow.setFillColor(sf::Color::Yellow);
}

ScoreNow::~ScoreNow()
{
}