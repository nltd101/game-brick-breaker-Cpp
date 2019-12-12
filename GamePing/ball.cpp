#include "pch.h"

#include "ball.h"

Ball::Ball()
{
	ball.setRadius(ballRadius - 3);
	ball.setOutlineThickness(0);
	//ball.setOutlineColor(sf::Color::Red);
	ball.setFillColor(sf::Color::Red);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
}
Ball::~Ball()
{

}