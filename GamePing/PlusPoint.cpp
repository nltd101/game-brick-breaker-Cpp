#include "pch.h"
#include "PlusPoint.h"
PlusPoint::PlusPoint()
{
	plus.loadFromFile("icon/coinicon.png");
	Sprite dHeart(plus);
	this->setTexture(plus);
	this->setOrigin(30, 30);
}

int PlusPoint::getLable()
{
	return 4;
}


PlusPoint::~PlusPoint()
{
}