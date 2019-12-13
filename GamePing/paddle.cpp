#include "pch.h"
#include "paddle.h"
paddle::paddle()
{
	Paddle.setSize(paddleSizeConst - sf::Vector2f(3, 3));
	Paddle.setOutlineThickness(3);
	Paddle.setOutlineColor(sf::Color::Black);
	Paddle.setFillColor(sf::Color(100, 100, 200));
	Paddle.setOrigin(paddleSizeConst / 2.f);
}
