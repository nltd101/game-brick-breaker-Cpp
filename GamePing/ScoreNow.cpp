#include "pch.h"
#include "ScoreNow.h"


ScoreNow::ScoreNow()
{
	font.loadFromFile("resources/zorque.ttf");
	this->scoreNow.setStyle(sf::Text::Bold);
	this->scoreNow.setFont(font);
	this->scoreNow.setCharacterSize(50);
	this->scoreNow.setPosition(600, 0);
	this->scoreNow.setFillColor(sf::Color::Red);
	sf::Texture texture;
	if (!texture.loadFromFile("img/moneyicon.png"))
	{
	}
	sf::Sprite sprite(texture);
	this->iconScore =sprite;
}

ScoreNow::~ScoreNow()
{
}