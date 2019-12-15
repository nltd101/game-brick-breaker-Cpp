#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 5
class Menu
{
private:
	int selectedItem;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
public:
	Menu();
	~Menu();
	void draw(sf::RenderWindow& Window);
	void MoveUp();
	void MoveDown();
	int getPressedItem();
};


