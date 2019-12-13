#include "pch.h"
#include "HideHeart.h"
int HideHeart::getLable()
{
	return 2;
}
HideHeart::HideHeart()
{
	heart.loadFromFile("icon/hidehearticon.png");
	Sprite dHeart(heart);
	this->setTexture(heart);
	this->setOrigin(30, 30);
}


HideHeart::~HideHeart()
{
}