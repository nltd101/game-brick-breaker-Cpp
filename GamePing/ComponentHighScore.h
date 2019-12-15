#pragma once
#include "ListViewHighScore.h"
#include "SFML/Graphics.hpp"
#include "Score.h"
#include "IconWindows.h"
class ComponentHighScore
{
public:
	ComponentHighScore();
	void run(int);
private:
	int windownWidth = 1000;
	int windownHeight = 700;
	string convertToString(int i)
	{
		stringstream ss;
		ss << i;
		return ss.str();
	}
	sf::RenderWindow hWindow;
	void processEvent(int);
	string playerInput = "";
	sf::Text inputName;
	string lableInputName;
	ListViewHighScore listView;
	Score score;
	
};

