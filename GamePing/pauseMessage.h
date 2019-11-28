#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class pauseMessage
{
public:
	sf::Text message;
	sf::Font font;
	pauseMessage();
	~pauseMessage();
};

