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
#include "HideHeart.h"
#include"ResizePaddle.h"
#include "PlusPoint.h"
#include "GenerateMapBaseLevel.h"
#include "SaveTraceBall.h"
#include "SoundBrick.h"
#include "MinusPaddle.h"
using namespace sf;
class Game
{
private:
	MinusPaddle minus;
	SoundBrick sound_Brick;
	int countBrick;
	int level = 1;
	BackgroundInfo background;
	sf::Vector2f paddleSize = paddleSizeConst;
	HideHeart hide_heart;
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
	vector<item*>listFaltItem;
	SaveTraceBall shadow;
	sf::RenderWindow mWindow;
	void processEvents();
	void update(int);
	void render();
	void processCollision(int ,int);
	void drawBrick();
	void rules_game();
public:
	Game();
	void run();
};
