#include "pch.h"

#include "ball.h"

Ball::Ball()
{
	ball.setRadius(ballRadius);
	//ball.setOutlineColor(sf::Color::Red);
	ball.setFillColor(sf::Color::Red);
	ball.setOrigin(ballRadius , ballRadius);
}
Ball::~Ball()
{

}