#pragma once
#include "ListViewHighScore.h"
#include "SFML/Graphics.hpp"
#include "Score.h"
#include "IconWindows.h"
class ComponentHighScore
{
public:
	int windownWidth = 1000;
	int windownHeight = 700;
	sf::Text inputName;
	string lableInputName;
	ListViewHighScore listView;
	ComponentHighScore();
	Score score;
	void run(int);
private:
	string convertToString(int i)
	{
		stringstream ss;
		ss << i;
		return ss.str();
	}
	sf::RenderWindow hWindow;
	void processEvent(int);
	string playerInput = "";
	
};

