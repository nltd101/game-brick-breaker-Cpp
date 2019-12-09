#include "pch.h"
#include "ComponentHighScore.h"
ComponentHighScore::ComponentHighScore()
	:hWindow(sf::VideoMode(windownWidth, windownHeight, 32), "HighScore", sf::Style::Titlebar | sf::Style::Close)
{
}
void ComponentHighScore::run()
{
	hWindow.setVerticalSyncEnabled(true);
	while (hWindow.isOpen())
	{
		processEvent();
		hWindow.clear(sf::Color(238, 232, 170));
		listView.draw(hWindow);
		hWindow.display();
	}
}

void ComponentHighScore::processEvent()
{
		sf::Event event;
		while (hWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)

				hWindow.close();

			switch (event.type)
			{
			case sf::Event::KeyReleased:
				hWindow.close();
				break;
			default: break;
			}
		}
}
