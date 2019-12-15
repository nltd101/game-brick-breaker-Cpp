#pragma once
#include <SFML/Graphics.hpp>
#include "item.h"
using namespace sf;
class MinusPaddle :public item
{
public:
	sf::Texture minus_paddle;
	MinusPaddle();
	int getLable();
	~MinusPaddle();
};
