#include "pch.h"
#include "ScoreNow.h"


ScoreNow::ScoreNow()
{
	font.loadFromFile("resources/zorque.ttf");
	this->scoreNow.setStyle(sf::Text::Bold);
	this->scoreNow.setFont(font);
	this->scoreNow.setCharacterSize(60);
	this->scoreNow.setPosition(900, 240);
	this->scoreNow.setFillColor(sf::Color::Yellow);
}

ScoreNow::~ScoreNow()
{
}