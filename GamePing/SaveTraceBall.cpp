#include "pch.h"
#include "SaveTraceBall.h"

void SaveTraceBall::newMove(int x, int y, sf::RenderWindow& mwindow)
{
	sf::CircleShape* saveball = new sf::CircleShape;
	saveball->setRadius(ballRadius);
	saveball->setOutlineThickness(0);
	saveball->setFillColor(sf::Color::White);
	saveball->setOrigin(ballRadius, ballRadius);
	saveball->setPosition(x, y);
	this->listSprite.push_back(saveball);
	if (this->listSprite.size() > 15)
	{
		this->listSprite.pop_front();
	}
	drawShadow(mwindow);
}

void SaveTraceBall::drawShadow(sf::RenderWindow& mwindow)
{
	int t = 15;
	for (auto i :this->listSprite)
	{
		t--;
		i->setRadius(ballRadius - t);
		mwindow.draw(*i);
	}
}
