#include "pch.h"
#include "SoundBrick.h"

SoundBrick::SoundBrick()
{
	//sound_brick.loadFromFile("music/Paddle.wav");
	this->sound.setBuffer(sound_brick);
}

SoundBrick::~SoundBrick()
{
}
