#pragma once
#include <SFML/Graphics.hpp>
#include "item.h"
using namespace sf;
class HideHeart:public item
{
public:
	sf::Texture heart;
	int getLable();
	HideHeart();
	~HideHeart();
};
