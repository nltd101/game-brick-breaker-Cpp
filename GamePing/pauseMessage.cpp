#include "pch.h"
#include "pauseMessage.h"


pauseMessage::pauseMessage()
{
	font.loadFromFile("resources/sansation.ttf");
	this->message.setFont(font);
	this->message.setCharacterSize(50);
	this->message.setPosition(825.f, 40.f);
	this->message.setFillColor(sf::Color::Red);
}


pauseMessage::~pauseMessage()
{
}
