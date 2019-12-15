#include "pch.h"
#include "ComponentHighScore.h"
ComponentHighScore::ComponentHighScore()
	:hWindow(sf::VideoMode(windownWidth, windownHeight, 32), "HighScore", sf::Style::Titlebar | sf::Style::Close)
{
}
void ComponentHighScore::run(int score)
{
	hWindow.setVerticalSyncEnabled(true);
	iconHighScore(hWindow);
	
	lableInputName = "Your score is " + convertToString(score) + ", please input your name: ";
	sf::Font font;
	
	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		//handle error
	}
	inputName.setFont(font);
	inputName.setCharacterSize(25);
	inputName.setPosition(sf::Vector2f(200, 600));
	inputName.setFillColor(sf::Color(0, 0, 135));
	inputName.setString(lableInputName+"...");
	while (hWindow.isOpen())
	{
		processEvent(score);
		hWindow.clear(sf::Color(238, 232, 170));
		listView.draw(hWindow);
		if (score != 0)
		{
			hWindow.draw(inputName);
			sf::Event event;
		}
		hWindow.display();
	}
	
}

bool checkNameInput(char code) {
	if (code == 95) return true;
	if((code>=97)&& (code <= 122)) return true;
	if ((code >= 65) && (code <= 90)) return true;
	return false;
};

void ComponentHighScore::processEvent(int score)
{
	sf::Event event; 
	while (hWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			hWindow.close();
		if (score != 0)
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.key.code != sf::Keyboard::Space)
				{
					if (checkNameInput(event.text.unicode))
					{
						this->playerInput += event.text.unicode;		
					}
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Backspace)
				{
					this->playerInput = this->playerInput.substr(0, playerInput.length() - 1);
				}
				inputName.setString(lableInputName+ this->playerInput);
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (playerInput.length()!=0)
					{
						Score(playerInput, convertToString(score)).pushScore();
					}
					hWindow.close();
					
				}
			}
		}
		else
		{
			if (event.type == sf::Event::KeyPressed)
			{
				hWindow.close();
			}
		}
	}
}
