#include "pch.h"
#include "ResizePaddle.h"
ResizePaddle::ResizePaddle()
{
	resize_paddle.loadFromFile("icon/reisizepaddleicon.png");
	Sprite dHeart(resize_paddle);
	this->setTexture(resize_paddle);
	this->setOrigin(30, 30);
}

int ResizePaddle::getLable()
{
	return 3;
}


ResizePaddle::~ResizePaddle()
{
}