#pragma once
#include "ListViewHighScore.h"
class ComponentHighScore
{
public:
	int windownWidth = 900;
	int windownHeight = 600;
	ListViewHighScore listView;
	ComponentHighScore();
	void run();
private:

	sf::RenderWindow hWindow;
	void processEvent();
	
};

