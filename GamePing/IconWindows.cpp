#include "pch.h"
#include "IconWindows.h"

void iconMain(sf::RenderWindow &mWindow)
{
	sf::Image icon;
	icon.loadFromFile("icon_laucher/iconmain2.png"); 
	mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void iconHighScore(sf::RenderWindow& mWindow)
{
	sf::Image icon;
	icon.loadFromFile("icon_laucher/highscore_icon.png");
	mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void iconGameRules(sf::RenderWindow& mWindow)
{
	sf::Image icon;
	icon.loadFromFile("icon_laucher/question.png");
	mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
