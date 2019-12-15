#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Heart
{
public:
	sf::Text heart;
	Heart();
	~Heart();
private:
	sf::Font font;
};

