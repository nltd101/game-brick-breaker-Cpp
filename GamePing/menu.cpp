#include"pch.h"
#include "menu.h"	
#include <SFML/Network.hpp>
#include <iostream>
Menu::Menu()
{
	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		//handle error
	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(50);
	menu[0].setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("1 PLAYER");
	menu[1].setFont(font);
	menu[1].setCharacterSize(50);
	menu[1].setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("MACHINE PLAYER");
	menu[2].setFont(font);
	menu[2].setCharacterSize(50);
	menu[2].setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("HIGH SCORE");
	menu[3].setFont(font);
	menu[3].setCharacterSize(50);
	menu[3].setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS + 1) * 4));
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("SETTING");
	menu[4].setFont(font);
	menu[4].setCharacterSize(50);
	menu[4].setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS + 1) * 5));
	menu[4].setFillColor(sf::Color::White);
	menu[4].setString("QUIT");
	selectedItem = 0;
}

Menu::~Menu()
{
}
void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(this->menu[i]);
	}
}
void Menu::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Red);

	}
}
void Menu::MoveDown()
{
	if (selectedItem + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}