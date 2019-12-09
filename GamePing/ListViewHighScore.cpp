#include "pch.h"
#include "ListViewHighScore.h"

ListViewHighScore::ListViewHighScore()
{
	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		//handle error
	}
	TopHighScore top;
	vector<Score*> listScore = top.getHighScore() ;
	int i = 1;
	for (vector<Score*>::iterator itscore = listScore.begin(); itscore != listScore.end(); itscore++)
	{
		sf::Text* it = new sf::Text;
		(*(it)).setFont(font);
		(*(it)).setCharacterSize(50);
		(*(it)).setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS + 1) * i));
		i++;
		(*(it)).setFillColor(sf::Color::Red);
		(*(it)).setString((*itscore)->get_name()+" : "+(*itscore)->get_score());
		this->listView.push_back(it);
	}
}

void ListViewHighScore::draw(sf::RenderWindow& window)
{
	for (vector<sf::Text*>::iterator it = this->listView.begin(); it!=this->listView.end(); it++)
	{
		window.draw((**it));
	}
}

ListViewHighScore::~ListViewHighScore()
{
}
