#include "pch.h"
#include "IconWindows.h"

void iconMain(sf::RenderWindow &mWindow)
{
	sf::Image icon;
	icon.loadFromFile("img/hearticon.png"); // File/Image/Pixel
	mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
