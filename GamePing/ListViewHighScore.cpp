#include "pch.h"
#include "ListViewHighScore.h"

ListViewHighScore::ListViewHighScore()
{

	if (!font1.loadFromFile("resources/neuropol.ttf"))
	{

	}
	TopHighScore top;
	vector<Score*> listScore = top.getHighScore() ;
	int i = 1;
	for (vector<Score*>::iterator itscore = listScore.begin(); itscore != listScore.end(); itscore++)
	{
		sf::Text* it = new sf::Text;
		(*it).setStyle(sf::Text::Bold);
		(*(it)).setFont(font1);
		(*(it)).setCharacterSize(50);
		(*(it)).setPosition(sf::Vector2f(350, 30 +600 / (MAX_NUMBER_OF_ITEMS + 2) * i));
		(*(it)).setFillColor(sf::Color::Red);
		(*(it)).setString((*itscore)->get_name()+" : "+(*itscore)->get_score());
		this->listView.push_back(it);
		i++;
	}
	if (!font.loadFromFile("resources/zorque.ttf"))
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
	int i = 0;
	for (vector<sf::Text*>::iterator it = this->listView.begin(); it!=this->listView.end(); it++)
	{
		window.draw((**it));
		sf::Texture textTure;
		i++;
		switch (i)
		{
		case 1:
			textTure.loadFromFile("icon/firsticon.png");
			break;
		case 2:
			textTure.loadFromFile("icon/secoundicon.png");
			break;
		case 3:
			textTure.loadFromFile("icon/thirdicon.png");
			break;
		default:
			break;
		}
		sf::Sprite icon;
		icon.setTexture(textTure);
		icon.setPosition(sf::Vector2f(275, 30 + 600 / (MAX_NUMBER_OF_ITEMS + 2) * i));
		window.draw(icon);
	}
	window.draw(this->txtHighscore);
}

ListViewHighScore::~ListViewHighScore()
{
}
