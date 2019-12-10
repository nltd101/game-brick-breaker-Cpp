#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class ScoreNow
{
public:
	sf::Text scoreNow;
	sf::Font font;
	sf::Sprite iconScore;
	ScoreNow();
	~ScoreNow();
};
