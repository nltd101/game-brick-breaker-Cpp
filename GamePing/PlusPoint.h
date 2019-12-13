#pragma once
#include <SFML/Graphics.hpp>
#include "item.h"
using namespace sf;
class PlusPoint :public item
{
public:
	sf::Texture plus;
	PlusPoint();
	int getLable();
	~PlusPoint();
};

