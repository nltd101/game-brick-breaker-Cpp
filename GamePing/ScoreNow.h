#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class ScoreNow
{
private:
	sf::Font font;
public:
	sf::Text scoreNow;
	sf::Sprite iconScore;
	ScoreNow();
	~ScoreNow();
};
