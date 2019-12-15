#include "pch.h"
#include "MinusPaddle.h"
MinusPaddle::MinusPaddle()
{
	minus_paddle.loadFromFile("icon/minusicon.png");
	Sprite dHeart(minus_paddle);
	this->setTexture(minus_paddle);
	this->setOrigin(30, 30);
}

int MinusPaddle::getLable()
{
	return 5;
}


MinusPaddle::~MinusPaddle()
{
}