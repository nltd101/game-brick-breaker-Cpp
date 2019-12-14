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
	ballSpeed = 500.f;
	ballAngle = 0.f;
	increase = 50.f;
	pi = 3.14159f;
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
				(left.Paddle.getPosition().x + paddleSize.x / 2 < gameWidth - Backsize.x + 10.f))
			{
				left.Paddle.move(paddleSpeed * deltaTime, 0.f);
			}
			std::string out_string;
			std::stringstream ss;
			ss << score;
			out_string = ss.str();
			text1.scoreNow.setString(out_string);
			out_string = "";
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 10; j++) {
					if (positionBrickLevel[i][j] != 0)
					{
						int xbrick = 45 + 90 * i;
						int ybrick = 15 + 30 * j;
						if ((this->pong.ball.getPosition().x > xbrick - 45) && (this->pong.ball.getPosition().x < xbrick + 45))//o giua ben phai va trai
						{
							//cham duoic gach
							if ((this->pong.ball.getPosition().y + this->pong.ballRadius > ybrick - 15)
								&& ((this->pong.ball.getPosition().y + this->pong.ballRadius < ybrick + 15)))
							{
								ballAngle = pi - ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ball.getPosition().y - 0.1f);
								processCollision(i, j);
							}
							//cham tren gach
							if ((this->pong.ball.getPosition().y - this->pong.ballRadius > ybrick - 15)
								&& ((this->pong.ball.getPosition().y - this->pong.ballRadius < ybrick + 15)))
							{
								ballAngle = pi - ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ball.getPosition().y + 0.1f);
								processCollision(i, j);
							}
						}
						if ((this->pong.ball.getPosition().y > ybrick - 15) && (this->pong.ball.getPosition().y < ybrick + 15))//o giua tren va duoi
						{
							//cham trai gach
							if ((this->pong.ball.getPosition().x + this->pong.ballRadius > xbrick - 45)
								&& ((this->pong.ball.getPosition().x + this->pong.ballRadius < xbrick + 45)))
							{
								ballAngle = - ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x - 0.1f, this->pong.ball.getPosition().y);
								processCollision(i, j);
							}
							//cham phai gach
							if ((this->pong.ball.getPosition().x - this->pong.ballRadius > xbrick - 45)
								&& ((this->pong.ball.getPosition().x - this->pong.ballRadius < xbrick + 45)))
							{
								ballAngle = -ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x - 0.1f, this->pong.ball.getPosition().y);
								processCollision(i, j);
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
				if ((*i)->getPosition().y > gameHeight - paddleSize.y)
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
							paddleSize.x += 50;
							break;
						case 4:
							score += 10 + rand() % 11;
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
				this->pong.ball.setPosition(this->pong.ballRadius + 0.1f, this->pong.ball.getPosition().y);
			}
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > gameWidth - Backsize.x + 15.f)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(gameWidth - this->pong.ballRadius - Backsize.x +15.f, this->pong.ball.getPosition().y);
			}
			if (this->pong.ball.getPosition().y - this->pong.ballRadius < 0.f)
			{
				ballAngle = pi - ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ballRadius + 0.1f);
			}
			std::string out_string1;
			std::stringstream st;
			st << life;
			out_string1 = st.str();
			textHeart.heart.setString(out_string1);
			if (this->pong.ball.getPosition().y + this->pong.ballRadius > gameHeight)
			{
				isPlaying = false;
				ballSpeed = 300.f;
				pong.ball.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y - this->pong.ballRadius - 0.1f);
				left.Paddle.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y / 2);
				paddleSize = paddleSizeConst;
				life = life - 1;
				
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
				ballSpeed += increase;
				ballAngle = pi - ballAngle -((delta)* 30* pi) / (paddleSize.x*90);
				pong.ball.setOutlineColor(sf::Color(rand() % 150, rand() % 150, rand() % 150));
				pong.ball.setFillColor(sf::Color(rand() % 225, rand() % 255, rand() % 255));
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->left.Paddle.getPosition().y - this->pong.ballRadius - paddleSize.y / 2 - 0.1f);
			}
		}


		if (mode == 1)
		{
			float deltaTime = clock.restart().asSeconds();
			float i = 1.0;
			int xpaddle = left.Paddle.getPosition().x;
			int ypaddle = left.Paddle.getPosition().y;
			int xball = pong.ball.getPosition().x;
			int yball = pong.ball.getPosition().y;
			int height = 250;
			if ((pong.ball.getPosition().y > height)&&(cos(ballAngle)>0))
			{
				int distance = ((gameHeight - yball) * tan(ballAngle) - xpaddle + xball);
				if (distance<paddleSize.x/2)
				{
					distance = -distance;
				}
				if (distance > gameWidth-paddleSize.x / 2)
				{
					distance = gameWidth-(distance-(gameWidth-paddleSize.x/2));
				}
				left.Paddle.move((distance* ballSpeed*cos(ballAngle) / (gameHeight - yball)), 0.f);
				//left.Paddle.move(1.f, 0.f);
			}
			
			/*if (((rightPaddleSpeed < 0.f) && (left.Paddle.getPosition().x - paddleSize.x / 2 > 10.f)) ||
				((rightPaddleSpeed > 0.f) && (left.Paddle.getPosition().x + paddleSize.x / 2 < gameWidth - Backsize.x + 10.f)))
			{
				left.Paddle.move(rightPaddleSpeed* deltaTime, 0.f);
			}
			//update ai
			if (AITimer.getElapsedTime() > AITime)
			{
				AITimer.restart();
				if (pong.ball.getPosition().x + pong.ballRadius > left.Paddle.getPosition().x + paddleSize.y / 2)
					rightPaddleSpeed = paddleSpeed;
				else if (pong.ball.getPosition().x - pong.ballRadius < left.Paddle.getPosition().x - paddleSize.y / 2)
					rightPaddleSpeed = -paddleSpeed;
				else
					rightPaddleSpeed = 0.f;
			}*/
			std::string out_string;
			std::stringstream ss;
			ss << score;
			out_string = ss.str();
			text1.scoreNow.setString(out_string);
			out_string = "";
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 10; j++) {
					if (positionBrickLevel[i][j] != 0)
					{
						int xbrick = 45 + 90 * i;
						int ybrick = 15 + 30 * j;
						if ((this->pong.ball.getPosition().x > xbrick - 45) && (this->pong.ball.getPosition().x < xbrick + 45))//o giua ben phai va trai
						{
							//cham duoic gach
							if ((this->pong.ball.getPosition().y + this->pong.ballRadius > ybrick - 15)
								&& ((this->pong.ball.getPosition().y + this->pong.ballRadius < ybrick + 15)))
							{
								ballAngle = pi - ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ball.getPosition().y - 0.1f);
								processCollision(i, j);
							}
							//cham tren gach
							if ((this->pong.ball.getPosition().y - this->pong.ballRadius > ybrick - 15)
								&& ((this->pong.ball.getPosition().y - this->pong.ballRadius < ybrick + 15)))
							{
								ballAngle = pi - ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ball.getPosition().y + 0.1f);
								processCollision(i, j);
							}
						}
						if ((this->pong.ball.getPosition().y > ybrick - 15) && (this->pong.ball.getPosition().y < ybrick + 15))//o giua tren va duoi
						{
							//cham trai gach
							if ((this->pong.ball.getPosition().x + this->pong.ballRadius > xbrick - 45)
								&& ((this->pong.ball.getPosition().x + this->pong.ballRadius < xbrick + 45)))
							{
								ballAngle = -ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x - 0.1f, this->pong.ball.getPosition().y);
								processCollision(i, j);
							}
							//cham phai gach
							if ((this->pong.ball.getPosition().x - this->pong.ballRadius > xbrick - 45)
								&& ((this->pong.ball.getPosition().x - this->pong.ballRadius < xbrick + 45)))
							{
								ballAngle = -ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x - 0.1f, this->pong.ball.getPosition().y);
								processCollision(i, j);
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
				if ((*i)->getPosition().y > gameHeight - paddleSize.y)
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
							paddleSize.x += 50;
							break;
						case 4:
							score += 10 + rand() % 11;
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
				this->pong.ball.setPosition(this->pong.ballRadius + 0.1f, this->pong.ball.getPosition().y);
			}
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > gameWidth - Backsize.x + 15.f)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(gameWidth - this->pong.ballRadius - Backsize.x + 15.f, this->pong.ball.getPosition().y);
			}
			if (this->pong.ball.getPosition().y - this->pong.ballRadius < 0.f)
			{
				ballAngle = pi - ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ballRadius + 0.1f);
			}
			std::string out_string1;
			std::stringstream st;
			st << life;
			out_string1 = st.str();
			textHeart.heart.setString(out_string1);
			if (this->pong.ball.getPosition().y + this->pong.ballRadius > gameHeight)
			{
				isPlaying = false;
				ballSpeed = 300.f;
				pong.ball.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y - this->pong.ballRadius - 0.1f);
				left.Paddle.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y / 2);
				paddleSize = paddleSizeConst;
				life = life - 1;

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
				ballSpeed += increase;
				ballAngle = pi - ballAngle - ((delta) * 30 * pi) / (paddleSize.x * 90);
				pong.ball.setOutlineColor(sf::Color(rand() % 150, rand() % 150, rand() % 150));
				pong.ball.setFillColor(sf::Color(rand() % 225, rand() % 255, rand() % 255));
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->left.Paddle.getPosition().y - this->pong.ballRadius - paddleSize.y / 2 - 0.1f);
			}
		}
	}

}
void Game::render()
{
	mWindow.clear(Color(238, 232, 170));
	// Draw
	shadow.newMove(pong.ball.getPosition().x, pong.ball.getPosition().y, mWindow);
	Sprite mHeart(hide_heart.heart);
	mHeart.setPosition(830, 150);
	Texture score_now;
	score_now.loadFromFile("img/moneyicon.png");
	Sprite mScore_now(score_now);
	mScore_now.setPosition(830, 250);
	left.Paddle.setSize(paddleSize);
	left.Paddle.setOrigin(paddleSize.x / 2, paddleSize.y / 2);
	std::string out_string;
	std::stringstream st;
	st << "Level: " << level + 1 << "";
	out_string = st.str();
	text.message.setString(out_string);
	
	if (isPlaying)
	{
		//mWindow.draw(mBackground);
		mWindow.draw(left.Paddle);
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
			this->pong.ball.setPosition(450, 550);
			ballAngle = (0.7 + ((double)(rand() % 4)) / 10) * pi;
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
			list.draw(mWindow);
		}
		else
		{
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
	default:
		break;
	}
	positionBrickLevel[i][j] = 0;
	cout << countBrick << endl;
	score = score + 5;
	

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
void opentHighScore() {
	ComponentHighScore component;
	component.run(0);
}
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type== sf::Event::Closed)
			mWindow.close();
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
							left.Paddle.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y / 2);
							pong.ball.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y - pong.ballRadius);
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
							pong.ball.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y - pong.ballRadius);
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
						break;
					case 4:
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
					left.Paddle.setPosition((gameWidth - Backsize.x) / 2, gameHeight - paddleSize.y / 2);
					pong.ball.setPosition((gameWidth - Backsize.x) / 2, gameHeight - this->pong.ballRadius - 0.1f);
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
		while (life != 0 && level != 2)
		{
			processEvents();
			update(mode);
			render();
		}
		ComponentHighScore().run(score);
	}
}
