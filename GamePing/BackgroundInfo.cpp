#include "pch.h"
#include "BackgroundInfo.h"

BackgroundInfo::BackgroundInfo()
{
	backgroundInfo.setSize(Backsize - sf::Vector2f(3, 0));
	backgroundInfo.setFillColor(sf::Color(0, 192, 255));
	backgroundInfo.setOutlineThickness(3);
	backgroundInfo.setOrigin(Backsize / 2.f);
	backgroundInfo.setPosition(900 + 17, 350);
}