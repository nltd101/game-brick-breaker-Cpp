#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Ball
{
public:
	float ballRadius = 15.f;
	sf::CircleShape ball;
	Ball();
	~Ball();
};

