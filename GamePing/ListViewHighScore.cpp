#include "pch.h"
#include "ListViewHighScore.h"

ListViewHighScore::ListViewHighScore()
{
	font.loadFromFile("resources/zorque.ttf");
	TopHighScore top;
	vector<Score*> listScore = top.getHighScore() ;
	int i = 1;
	for (vector<Score*>::iterator itscore = listScore.begin(); itscore != listScore.end(); itscore++)
	{
		sf::Text* it = new sf::Text;
		(*it).setStyle(sf::Text::Bold);
		(*(it)).setFont(font);
		(*(it)).setCharacterSize(50);
		(*(it)).setPosition(sf::Vector2f(350, 30 +600 / (MAX_NUMBER_OF_ITEMS + 2) * i));
		i++;
		(*(it)).setFillColor(sf::Color::Red);
		(*(it)).setString((*itscore)->get_name()+" : "+(*itscore)->get_score());
		this->listView.push_back(it);
	}
	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		//handle error
	}
	txtHighscore.setFont(font);
	txtHighscore.setCharacterSize(65);
	txtHighscore.setPosition(sf::Vector2f(180, 20));
	txtHighscore.setFillColor(sf::Color(2, 2, 37));
	txtHighscore.setString("Top 5 Highest Score");
}

void ListViewHighScore::draw(sf::RenderWindow& window)
{
	for (vector<sf::Text*>::iterator it = this->listView.begin(); it!=this->listView.end(); it++)
	{
		window.draw((**it));
	}
	window.draw(this->txtHighscore);
}

ListViewHighScore::~ListViewHighScore()
{
}
