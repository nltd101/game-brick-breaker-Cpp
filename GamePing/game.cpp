#include "pch.h"
#include "game.h"
#include "SFML/Audio.hpp"
#include <iostream>
#include <sstream>
using namespace std;
Game::Game()
	:mWindow(sf::VideoMode(gameWidth, gameHeight, 32), "Brick Game", sf::Style::Titlebar | sf::Style::Close)
{
	isPlaying = false;
	AITime = sf::seconds(0.1f);
	paddleSpeed = 600.f;
	rightPaddleSpeed = 0.f;
	ballSpeed = 300.f;
	ballAngle = 0.f;
	increase = 50.f;
	pi = 3.14159265359f;
	isFirstTime = true;
}
void Game::update(int mode)
{
	if (isPlaying)
	{
		if (mode == 0)
		{
			float deltaTime = clock.restart().asSeconds();
			// Move the player's paddle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
				(left.Paddle.getPosition().x -paddleSize.x / 2 > 10.f))
			{
				left.Paddle.move(-paddleSpeed * deltaTime, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
				(left.Paddle.getPosition().x + paddleSize.x / 2 < gameWidth - Backsize.x ))
			{
				left.Paddle.move(paddleSpeed * deltaTime, 0.f);
			}
			std::string out_string;
			std::stringstream ss;
			ss << score;
			out_string = ss.str();
			text1.scoreNow.setString(out_string);
			out_string = "";
			bool check = true;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 10; j++) 
				{
					if (positionBrickLevel[i][j] != 0) {
						if (check)
						{
							int xbrick = 45 + 90 * i;
							int ybrick = 15 + 30 * j;
							if ((this->pong.ball.getPosition().x > xbrick - 45) && (this->pong.ball.getPosition().x < xbrick + 45))//o giua ben phai va trai
							{
								//cham duoic gach
								if ((this->pong.ball.getPosition().y + this->pong.ballRadius > ybrick - 15)
									&& ((this->pong.ball.getPosition().y + this->pong.ballRadius < ybrick)))
								{
									
										ballAngle = pi - (ballAngle);
									//this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ball.getPosition().y - 0.1f);
									this->pong.ball.setPosition(this->pong.ball.getPosition().x, ybrick - 15-pong.ballRadius);
									processCollision(i, j);
									check = false;
								}
								//cham tren gach
								if ((this->pong.ball.getPosition().y - this->pong.ballRadius > ybrick)
									&& ((this->pong.ball.getPosition().y - this->pong.ballRadius < ybrick + 15)))
								{
								
										ballAngle = pi - (ballAngle );
								
									this->pong.ball.setPosition(this->pong.ball.getPosition().x, ybrick + 15+pong.ballRadius);
									processCollision(i, j);
									check = false;
								}
							}
							if ((this->pong.ball.getPosition().y > ybrick - 15) && (this->pong.ball.getPosition().y < ybrick + 15))//o giua tren va duoi
							{
								//cham trai gach
								if ((this->pong.ball.getPosition().x + this->pong.ballRadius > xbrick - 45)
									&& ((this->pong.ball.getPosition().x + this->pong.ballRadius < xbrick-10)))
								{
									ballAngle = -ballAngle;
									this->pong.ball.setPosition(xbrick - 45-pong.ballRadius, this->pong.ball.getPosition().y);
									processCollision(i, j);
									check = false;
								}
								//cham phai gach
								if ((this->pong.ball.getPosition().x - this->pong.ballRadius > xbrick+10)
									&& ((this->pong.ball.getPosition().x - this->pong.ballRadius < xbrick + 45)))
								{
									ballAngle = -ballAngle;
									this->pong.ball.setPosition(xbrick + 45+pong.ballRadius, this->pong.ball.getPosition().y);
									processCollision(i, j);
									check = false;
								}
							}
						}
					}
				}
			}
			// Move the ball
			float factor = ballSpeed * deltaTime;
			this->pong.ball.move(std::sin(ballAngle)* factor, std::cos(ballAngle)* factor);
			for (vector<item*>::iterator i = listFaltItem.begin(); i != listFaltItem.end(); i++)
			{
				(*i)->move(0.f, 2.f);
				if ((*i)->getPosition().y > gameHeight - paddleSize.y - pong.ballRadius)
				{
					if (((*i)->getPosition().x < left.Paddle.getPosition().x + paddleSize.x / 2) &&
						((*i)->getPosition().x > left.Paddle.getPosition().x - paddleSize.x / 2))
					{
						switch ((*i)->getLable())
						{
						case 2:
							life++;
							break;
						case 3:
							if (paddleSize.x < 400)
							{
								paddleSize.x += 50;
							}
							sound_Brick.sound_brick.loadFromFile("music/Gold.wav");
							sound_Brick.sound.play();
							break;
						case 4:
							score += 10 + rand() % 11;
							sound_Brick.sound_brick.loadFromFile("music/Gold.wav");
							sound_Brick.sound.play();
							break;
						case 5:
							if (paddleSize.x > 100)
							{
								paddleSize.x -= 50;
							}
							sound_Brick.sound_brick.loadFromFile("music/Gold.wav");
							sound_Brick.sound.play();
							break;
						default:
							break;
						}
					}
					listFaltItem.erase(i);
					break;
				}
			}
			// Check collisions between the ball and the screen
			if (this->pong.ball.getPosition().x - this->pong.ballRadius < 0.f)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(this->pong.ballRadius + 0.01f, this->pong.ball.getPosition().y);
			}
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > gameWidth - Backsize.x + 15.f)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(gameWidth - this->pong.ballRadius - Backsize.x +15.f, this->pong.ball.getPosition().y);
			}
			if (this->pong.ball.getPosition().y - this->pong.ballRadius < 0.f)
			{
				ballAngle = pi - ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ballRadius + 0.01f);
			}
			std::string out_string1;
			std::stringstream st;
			st << life;
			out_string1 = st.str();
			textHeart.heart.setString(out_string1);
			if (this->pong.ball.getPosition().y + this->pong.ballRadius > gameHeight)
			{
				isPlaying = false;
				cout << ballSpeed;
				sound_Brick.sound_brick.loadFromFile("music/Fail.wav");
				sound_Brick.sound.play();
				ballSpeed = 300.f;
				pong.ball.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y - this->pong.ballRadius - 0.01f);
				left.Paddle.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y / 2);
				paddleSize = paddleSizeConst;
				life = life - 1;
				shadow.listSprite.clear();
			}
			if (life == 0)
			{
				isFirstTime = true;
			}
			// Check the collisions between the ball and the paddles
			// Left Paddle
			if (this->pong.ball.getPosition().x - this->pong.ballRadius <= left.Paddle.getPosition().x + paddleSize.x / 2 &&
				this->pong.ball.getPosition().x - this->pong.ballRadius >= left.Paddle.getPosition().x - paddleSize.x / 2 &&
				this->pong.ball.getPosition().y + this->pong.ballRadius >= left.Paddle.getPosition().y - paddleSize.y / 2 &&
				this->pong.ball.getPosition().y + this->pong.ballRadius <= left.Paddle.getPosition().y + paddleSize.y / 2)
			{
				int delta = this->pong.ball.getPosition().x - this->left.Paddle.getPosition().x;
				if (ballSpeed<1250)
				{
					ballSpeed += increase;
				}
				ballAngle = pi - ballAngle -((delta)* 30* pi) / (paddleSize.x*90);
				pong.ball.setFillColor(sf::Color(rand() % 150, rand() % 150, rand() % 150));
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->left.Paddle.getPosition().y - this->pong.ballRadius - paddleSize.y / 2 - 0.1f);
				sound_Brick.sound_brick.loadFromFile("music/Paddle.wav");
				sound_Brick.sound.play();
			}
		}

		if (mode == 1)
		{
			float deltaTime = clock.restart().asSeconds();
			// Move the player's paddle
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
				(left.Paddle.getPosition().x - paddleSize.x / 2 > 10.f))
			{
				left.Paddle.move(-paddleSpeed * deltaTime, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
				(left.Paddle.getPosition().x + paddleSize.x / 2 < gameWidth - Backsize.x))
			{
				left.Paddle.move(paddleSpeed * deltaTime, 0.f);
			}*/
			if (pong.ball.getPosition().x-paddleSize.x/2<=0)
			{
				left.Paddle.setPosition(paddleSize.x/2, gameHeight - paddleSize.y);
			}
			else
				if (pong.ball.getPosition().x + paddleSize.x / 2>gameWidth-Backsize.x)
				{
					left.Paddle.setPosition(pong.ball.getPosition().x - paddleSize.x / 2, gameHeight - paddleSize.y);
				}
				else
				left.Paddle.setPosition(pong.ball.getPosition().x,gameHeight - paddleSize.y);
			std::string out_string;
			std::stringstream ss;
			ss << score;
			out_string = ss.str();
			text1.scoreNow.setString(out_string);
			out_string = "";
			bool check = true;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (positionBrickLevel[i][j] != 0) {
						if (check)
						{
							int xbrick = 45 + 90 * i;
							int ybrick = 15 + 30 * j;
							if ((this->pong.ball.getPosition().x > xbrick - 45) && (this->pong.ball.getPosition().x < xbrick + 45))//o giua ben phai va trai
							{
								//cham duoic gach
								if ((this->pong.ball.getPosition().y + this->pong.ballRadius > ybrick - 15)
									&& ((this->pong.ball.getPosition().y + this->pong.ballRadius < ybrick)))
								{

									ballAngle = pi - (ballAngle);
									//this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ball.getPosition().y - 0.1f);
									this->pong.ball.setPosition(this->pong.ball.getPosition().x, ybrick - 15 - pong.ballRadius);
									processCollision(i, j);
									check = false;
								}
								//cham tren gach
								if ((this->pong.ball.getPosition().y - this->pong.ballRadius > ybrick)
									&& ((this->pong.ball.getPosition().y - this->pong.ballRadius < ybrick + 15)))
								{

									ballAngle = pi - (ballAngle);

									this->pong.ball.setPosition(this->pong.ball.getPosition().x, ybrick + 15 + pong.ballRadius);
									processCollision(i, j);
									check = false;
								}
							}
							if ((this->pong.ball.getPosition().y > ybrick - 15) && (this->pong.ball.getPosition().y < ybrick + 15))//o giua tren va duoi
							{
								//cham trai gach
								if ((this->pong.ball.getPosition().x + this->pong.ballRadius > xbrick - 45)
									&& ((this->pong.ball.getPosition().x + this->pong.ballRadius < xbrick - 10)))
								{
									ballAngle = -ballAngle;
									this->pong.ball.setPosition(xbrick - 45 - pong.ballRadius, this->pong.ball.getPosition().y);
									processCollision(i, j);
									check = false;
								}
								//cham phai gach
								if ((this->pong.ball.getPosition().x - this->pong.ballRadius > xbrick + 10)
									&& ((this->pong.ball.getPosition().x - this->pong.ballRadius < xbrick + 45)))
								{
									ballAngle = -ballAngle;
									this->pong.ball.setPosition(xbrick + 45 + pong.ballRadius, this->pong.ball.getPosition().y);
									processCollision(i, j);
									check = false;
								}
							}
						}
					}
				}
			}
			// Move the ball
			float factor = ballSpeed * deltaTime;
			this->pong.ball.move(std::sin(ballAngle) * factor, std::cos(ballAngle) * factor);
			for (vector<item*>::iterator i = listFaltItem.begin(); i != listFaltItem.end(); i++)
			{
				(*i)->move(0.f, 2.f);
				if ((*i)->getPosition().y > gameHeight - paddleSize.y - pong.ballRadius)
				{
					if (((*i)->getPosition().x < left.Paddle.getPosition().x + paddleSize.x / 2) &&
						((*i)->getPosition().x > left.Paddle.getPosition().x - paddleSize.x / 2))
					{
						switch ((*i)->getLable())
						{
						case 2:
							life++;
							break;
						case 3:
							if (paddleSize.x < 400)
							{
								paddleSize.x += 50;
							}
							sound_Brick.sound_brick.loadFromFile("music/Gold.wav");
							sound_Brick.sound.play();
							break;
						case 4:
							score += 10 + rand() % 11;
							sound_Brick.sound_brick.loadFromFile("music/Gold.wav");
							sound_Brick.sound.play();
							break;
						case 5:
							if (paddleSize.x > 100)
							{
								paddleSize.x -= 50;
							}
							sound_Brick.sound_brick.loadFromFile("music/Gold.wav");
							sound_Brick.sound.play();
							break;
						default:
							break;
						}
					}
					listFaltItem.erase(i);
					break;
				}
			}
			// Check collisions between the ball and the screen
			if (this->pong.ball.getPosition().x - this->pong.ballRadius < 0.f)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(this->pong.ballRadius + 0.01f, this->pong.ball.getPosition().y);
			}
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > gameWidth - Backsize.x + 15.f)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(gameWidth - this->pong.ballRadius - Backsize.x + 15.f, this->pong.ball.getPosition().y);
			}
			if (this->pong.ball.getPosition().y - this->pong.ballRadius < 0.f)
			{
				ballAngle = pi - ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ballRadius + 0.01f);
			}
			std::string out_string1;
			std::stringstream st;
			st << life;
			out_string1 = st.str();
			textHeart.heart.setString(out_string1);
			if (this->pong.ball.getPosition().y + this->pong.ballRadius > gameHeight)
			{
				isPlaying = false;
				cout << ballSpeed;
				sound_Brick.sound_brick.loadFromFile("music/Fail.wav");
				sound_Brick.sound.play();
				ballSpeed = 300.f;
				pong.ball.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y - this->pong.ballRadius - 0.01f);
				left.Paddle.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y / 2);
				paddleSize = paddleSizeConst;
				life = life - 1;
				shadow.listSprite.clear();
			}
			if (life == 0)
			{
				isFirstTime = true;
			}
			// Check the collisions between the ball and the paddles
			// Left Paddle
			if (this->pong.ball.getPosition().x - this->pong.ballRadius <= left.Paddle.getPosition().x + paddleSize.x / 2 &&
				this->pong.ball.getPosition().x - this->pong.ballRadius >= left.Paddle.getPosition().x - paddleSize.x / 2 &&
				this->pong.ball.getPosition().y + this->pong.ballRadius >= left.Paddle.getPosition().y - paddleSize.y / 2 &&
				this->pong.ball.getPosition().y + this->pong.ballRadius <= left.Paddle.getPosition().y + paddleSize.y / 2)
			{
				int delta = this->pong.ball.getPosition().x - this->left.Paddle.getPosition().x;
				if (ballSpeed < 1250)
				{
					ballSpeed += increase;
				}
				ballAngle = pi - ballAngle - ((delta) * 30 * pi) / (paddleSize.x * 90);
				pong.ball.setFillColor(sf::Color(rand() % 150, rand() % 150, rand() % 150));
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->left.Paddle.getPosition().y - this->pong.ballRadius - paddleSize.y / 2 - 0.1f);
				sound_Brick.sound_brick.loadFromFile("music/Paddle.wav");
				sound_Brick.sound.play();
			}
		}
	}
}
void Game::processCollision(int i, int j)
{
	item* item;
	switch (positionBrickLevel[i][j])
	{
	case 2:
		item = new HideHeart();
		item->setPosition(50 + 90 * i, 20 + 30 * j);
		listFaltItem.push_back(item);
		break;
	case 3:
		item = new ResizePaddle();
		item->setPosition(50 + 90 * i, 20 + 30 * j);
		listFaltItem.push_back(item);
		break;
	case 4:
		item = new PlusPoint();
		item->setPosition(50 + 90 * i, 20 + 30 * j);
		listFaltItem.push_back(item);
		break;
	case 5:
		item = new MinusPaddle();
		item->setPosition(50 + 90 * i, 20 + 30 * j);
		listFaltItem.push_back(item);
		break;
	default:
		break;
	}
	positionBrickLevel[i][j] = 0;
	cout << countBrick << endl;
	score = score + 5;
	sound_Brick.sound_brick.loadFromFile("music/Brick.wav");
	sound_Brick.sound.play();

}
void Game::drawBrick()
{
	countBrick = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (positionBrickLevel[i][j] != 0)
			{
				countBrick++;
				Brick brick;
				switch (j)
				{
				case 0:
					brick.BRICK.setFillColor(sf::Color(255, 144, 0));
					break;
				case 1:
					brick.BRICK.setFillColor(sf::Color(255, 198, 0));
					break;
				case 2:
					brick.BRICK.setFillColor(sf::Color(138, 255, 0));
					break;
				case 3:
					brick.BRICK.setFillColor(sf::Color(0, 255, 10));
					break;
				case 4:
					brick.BRICK.setFillColor(sf::Color(0, 192, 255));
					break;
				case 5:
					brick.BRICK.setFillColor(sf::Color(0, 12, 255));
					break;
				case 6:
					brick.BRICK.setFillColor(sf::Color(120, 0, 255));
					break;
				case 7:
					brick.BRICK.setFillColor(sf::Color(255, 0, 84));
					break;
				case 8:
					brick.BRICK.setFillColor(sf::Color(96, 57, 19));
					break;
				case 9:
				{
					brick.BRICK.setFillColor(sf::Color(0, 0, 0));
					break;
				}
				default:
					break;
				}
				brick.BRICK.setPosition(50 + 90 * i, 20 + 30 * j);
				mWindow.draw(brick.BRICK);
			}
		}
	}
}
void Game::render()
{
	
	// Draw
	Sprite mHeart(hide_heart.heart);
	mHeart.setPosition(825, 150);
	Texture score_now;
	score_now.loadFromFile("img/moneyicon.png");
	Sprite mScore_now(score_now);
	mScore_now.setPosition(825, 250);
	left.Paddle.setSize(paddleSize);
	left.Paddle.setOrigin(paddleSize.x / 2, paddleSize.y / 2);
	std::string out_string;
	std::stringstream st;
	st << "Level: " << level + 1 << "";
	out_string = st.str();
	text.message.setString(out_string);
	if (isPlaying)
	{
		mWindow.clear(Color(238, 232, 170));
		//mWindow.draw(mBackground);
		mWindow.draw(left.Paddle);
		shadow.newMove(pong.ball.getPosition().x, pong.ball.getPosition().y, mWindow);
		mWindow.draw(pong.ball);
		mWindow.draw(background.backgroundInfo);
		mWindow.draw(mHeart);
		mWindow.draw(mScore_now);
		mWindow.draw(text1.scoreNow);
		mWindow.draw(textHeart.heart);
		mWindow.draw(text.message);
		drawBrick();
		if (countBrick == 0)
		{
			level++;
			GenerateMapBaseLevel().setMapLevel(positionBrickLevel, level);
			this->pong.ball.setPosition(gameWidth / 2, gameHeight - paddleSize.y - pong.ballRadius - 0.1f);
			ballAngle = (0.7 + ((double)(rand() % 4)) / 10) * pi;
			ballSpeed = 300.f;
			this->shadow.listSprite.clear();
		}
		for (vector<item*>::iterator i = listFaltItem.begin(); i != listFaltItem.end(); i++)
		{
			mWindow.draw(**i);
		}
	}
	else
	{
		if (isFirstTime == true)
		{
			mWindow.clear(Color(57, 57, 187));
			list.draw(mWindow);
		}
		else
		{
			mWindow.clear(Color(238, 232, 170));
			mWindow.draw(left.Paddle);
			mWindow.draw(pong.ball);
			mWindow.draw(background.backgroundInfo);
			mWindow.draw(mHeart);
			mWindow.draw(mScore_now);
			mWindow.draw(text1.scoreNow);
			mWindow.draw(textHeart.heart);
			mWindow.draw(text.message);
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (positionBrickLevel[i][j] != 0)
					{
						Brick brick;
						switch (j)
						{
						case 0:
							brick.BRICK.setFillColor(sf::Color(255, 144, 0));
							break;
						case 1:
							brick.BRICK.setFillColor(sf::Color(255, 198, 0));
							break;
						case 2:
							brick.BRICK.setFillColor(sf::Color(138, 255, 0));
							break;
						case 3:
							brick.BRICK.setFillColor(sf::Color(0, 255, 10));
							break;
						case 4:
							brick.BRICK.setFillColor(sf::Color(0, 192, 255));
							break;
						case 5:
							brick.BRICK.setFillColor(sf::Color(0, 12, 255));
							break;
						case 6:
							brick.BRICK.setFillColor(sf::Color(120, 0, 255));
							break;
						case 7:
							brick.BRICK.setFillColor(sf::Color(255, 0, 84));
							break;
						case 8:
							brick.BRICK.setFillColor(sf::Color(96, 57, 19));
							break;
						case 9:
							brick.BRICK.setFillColor(sf::Color(0, 0, 0));
							break;
						default:
							break;
						}
						brick.BRICK.setPosition(50 + 90 * i, 20 + 30 * j);
						mWindow.draw(brick.BRICK);
					}
				}
			}
		}
	}

	// Display things on screen
	mWindow.display();
}

void Game::rules_game()
{
	RenderWindow window(sf::VideoMode(1000, 700), "RULES GAME");
	Texture texture;
	texture.loadFromFile("img/Screen.jpg");
	Sprite s1(texture);
	Font font3;
	font3.loadFromFile("resources/zorque.ttf");
	Text text("RULES AND HOW TO PLAY", font3);
	text.setPosition(150, 30);
	text.setFillColor(Color::Red);
	text.setCharacterSize(50);
	text.setOutlineThickness(1);
	text.setOutlineColor(Color::Green);
	Text text1("RULES", font3);
	text1.setPosition(30, 100);
	text1.setFillColor(Color::Red);
	text1.setCharacterSize(50);
	text1.setStyle(Text::Underlined | Text::Italic);
	Font font4;
	font4.loadFromFile("resources/sansation.ttf");
	// Neu luat le choi game
	Text text2("1. Players move to catch the ball.\n2. When the ball falls but the player have not\n catched it, the player lost 1 turn. After 3 rounds, \nthe player's result is saved.\n3. During the game, the player who has eaten \nthe heart is given 1 more turn.", font4);
	text2.setPosition(30, 165);
	text2.setFillColor(Color::Black);
	text2.setCharacterSize(45);
	Text text3("HOW TO PLAY", font3);
	text3.setPosition(30, 470);
	text3.setFillColor(Color::Red);
	text3.setCharacterSize(50);
	text3.setStyle(Text::Underlined | Text::Italic);
	Text text4(" - The player uses the A, D buttons to move the \nslider right and left.", font4);
	text4.setPosition(30, 530);
	text4.setFillColor(Color::Black);
	text4.setCharacterSize(45);
	iconGameRules(window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit;
			}
		}

		window.clear();
		window.draw(s1);
		window.draw(text);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);
		window.display();
	}

}
void opentHighScore() {
	ComponentHighScore component;
	component.run(0);
}
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			exit(0);
			mWindow.close(); 
		}
		if ((isPlaying == false) && isFirstTime == true)
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					list.MoveUp();
					break;
				case sf::Keyboard::Down:
					list.MoveDown();
					break;
				case sf::Keyboard::Enter:

					switch (list.getPressedItem())
					{
					case 0:
						mode = 0;
						if (!isPlaying)
						{
							isPlaying = true;
							isFirstTime = false;
							clock.restart();
							// Reset position
							left.Paddle.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y / 2 - 2.f);
							pong.ball.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y - pong.ballRadius - 0.1f);
							// Reset the ball
							do
							{
								ballAngle = (std::rand() % 360) * 2 * pi / 360;
							} while (std::abs(std::cos(ballAngle)) < 0.7f);
						}
						break;
					case 1:
						mode = 1;
						if (!isPlaying)
						{
							isPlaying = true;
							isFirstTime = false;
							clock.restart();
							// Reset position
							left.Paddle.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y / 2);
							pong.ball.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y - pong.ballRadius - 0.1f);
							// Reset the ball
							do
							{
								ballAngle = (std::rand() % 360) * 2 * pi / 360;
							} while (std::abs(std::cos(ballAngle)) < 0.7f);
						}
						break;
					case 2:
						opentHighScore();
						break;
					case 3:
						rules_game();
						break;
					case 4:
						exit(0);
						mWindow.close();
						
						break;
					default:
						break;
					}
				default:
					break;
				}
			default:
				break;
			}
		}
		if ((isFirstTime == false) && (isPlaying == false))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					isPlaying = true;
					clock.restart();

					// Reset the position of the paddles and ball
					left.Paddle.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y / 2 - 2.f);
					pong.ball.setPosition((gameWidth - Backsize.x) / 2, gameHeight - this->pong.ballRadius - paddleSize.y / 2 - 0.1f);
					// Reset the ball angle
					do
					{
						// Make sure the ball initial angle is not too much vertical
						ballAngle = (std::rand() % 360) * 2 * pi / 360;
					} while (std::abs(std::cos(ballAngle)) < 0.7f);
					break;
				case sf::Keyboard::Escape:
					isFirstTime = true;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
	}
}
void Game::run()
{
	mWindow.setVerticalSyncEnabled(true);
	isPlaying = false;
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	iconMain(mWindow);
	while (mWindow.isOpen())
	{
		life = 3;
		score = 0;
		level = 0;
		GenerateMapBaseLevel().setMapLevel(positionBrickLevel, level);
		while (life != 0)
		{
			processEvents();
			update(mode);
			render();
		}
		ComponentHighScore().run(score);
	}
}
