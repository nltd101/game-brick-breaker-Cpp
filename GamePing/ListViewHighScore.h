#pragma once
#include<SFML/Graphics.hpp>
#include "TopHighScore.h"
#define MAX_NUMBER_OF_ITEMS 5
class ListViewHighScore
{
private:
	int selectedItem;
	sf::Font font;
	sf::Font font1;
	vector<sf::Text*> listView;
	sf::Text txtHighscore;
public:
	ListViewHighScore();
	void draw(sf::RenderWindow& Window);
	~ListViewHighScore();
};

