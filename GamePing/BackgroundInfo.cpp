#include "pch.h"
#include "BackgroundInfo.h"

BackgroundInfo::BackgroundInfo()
{
	backgroundInfo.setSize(Backsize - sf::Vector2f(3, 0));
	backgroundInfo.setFillColor(sf::Color(100, 100, 200));
	backgroundInfo.setOrigin(Backsize / 2.f);
	backgroundInfo.setPosition(900 + 17, 350);
}
