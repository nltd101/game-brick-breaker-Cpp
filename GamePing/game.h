#pragma once
#include <SFML\Graphics.hpp>
#include "ball.h"
#include "pauseMessage.h"
#include "paddle.h"
#include "menu.h"
#include <ctime>
#include <string>
#include <cstdlib>
#include <cmath>
#include "Brick.h"
#include "ScoreNow.h"
#include "ComponentHighScore.h"
#include "Heart.h"
#include "IconWindows.h"
#include "BackgroundInfo.h"
using namespace sf;

class Game
{
public:
	int positionBrick[10][10] =
	{ {1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1},
	 {0,0,0,0,0,0,0,0,0,0} };
	BackgroundInfo background;
	Ball pong;
	paddle left;
	paddle right;
	ScoreNow text1;
	Heart textHeart;
	pauseMessage text;
	sf::Clock AITimer;
	sf::Clock clock;
	sf::Time AITime = sf::seconds(0.1f);
	int gameWidth = 1000;
	int gameHeight = 700;
	float paddleSpeed;
	float rightPaddleSpeed;
	float ballSpeed;
	float ballAngle;
	float pi;
	float increase;
	Menu list;
	bool isPlaying;
	bool isFirstTime;
	int mode = 0;
	int score = 1;
	int life = 3;
	int positionBrickLevel[10][10]; 
	Game();
	void run();
private:
	void processEvents();
	void update(int);
	void render();
private:
	sf::RenderWindow mWindow;
};
