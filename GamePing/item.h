#pragma once
#include <SFML/Graphics.hpp>
class item:public sf::Sprite
{
public:
	virtual int getLable()=0;
};

