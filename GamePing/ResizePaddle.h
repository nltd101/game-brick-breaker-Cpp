#pragma once
#include <SFML/Graphics.hpp>
#include "item.h"
using namespace sf;
class ResizePaddle :public item
{
public:
	sf::Texture resize_paddle;
	ResizePaddle();
	int getLable();
	~ResizePaddle();
};
