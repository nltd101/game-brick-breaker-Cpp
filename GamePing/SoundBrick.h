#pragma once
#include "SFML/Audio.hpp"
class SoundBrick
{
public:
	sf::SoundBuffer sound_brick;
	sf::Sound sound;
	SoundBrick();
	~SoundBrick();
};

