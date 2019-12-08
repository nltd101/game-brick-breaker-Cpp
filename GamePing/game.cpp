#include "pch.h"
#include "game.h"
#include "SFML/Audio.hpp"
#include <iostream>

using namespace std;
Game::Game()
	:mWindow(sf::VideoMode(gameWidth, gameHeight, 32), "PongGame", sf::Style::Titlebar | sf::Style::Close)
{
	isPlaying = false;
	AITime = sf::seconds(0.1f);
	paddleSpeed = 400.f;
	rightPaddleSpeed = 0.f;
	ballSpeed = 100.f;
	ballAngle = 0.f;
	increase = 40.f;
	pi = 3.14159f;
	//pi = 10.05f;
	isFirstTime = true;
}

void Game::run()
{
	mWindow.setVerticalSyncEnabled(true);
	isPlaying = false;
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	while (mWindow.isOpen())
	{
		processEvents();
		update(mode);
		render();
	}
}
void Game::update(int mode)
{
	if (isPlaying)
	{
		if (mode == 1)
		{
			float deltaTime = clock.restart().asSeconds();
			// Move the player's paddle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
				(left.Paddle.getPosition().y - paddleSize.y > 5.f))
			{
				left.Paddle.move(0.f, -paddleSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
				(left.Paddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
			{
				left.Paddle.move(0.f, paddleSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				(right.Paddle.getPosition().y - paddleSize.y / 2 > 5.f))
			{
				right.Paddle.move(0.f, -paddleSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				(right.Paddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
			{
				right.Paddle.move(0.f, paddleSpeed * deltaTime);
			}

			// Move the ball
			float factor = ballSpeed * deltaTime;
			this->pong.ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);
			// Check collisions between the ball and the screen
			if (this->pong.ball.getPosition().x - this->pong.ballRadius < 0.f)
			{
				isPlaying = false;
				text.message.setString("P2 won!!!\nPress space to restart or\nescape to exit");
				text.message.setFillColor(sf::Color::Blue);
				ballSpeed = 500.f;
			}
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > gameWidth)
			{
				isPlaying = false;
				text.message.setString("P1 won!\nPress space to restart or\nescape to exit");
				text.message.setFillColor(sf::Color::Blue);
				ballSpeed = 500.f;
			}
			if (this->pong.ball.getPosition().y - this->pong.ballRadius < 0.f)
			{

				ballAngle = -ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ballRadius + 0.1f);
			}
			if (this->pong.ball.getPosition().y + this->pong.ballRadius > gameHeight)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, gameHeight - this->pong.ballRadius - 0.1f);
			}

			// Check the collisions between the ball and the paddles
			// Left Paddle
			if (this->pong.ball.getPosition().x - this->pong.ballRadius < left.Paddle.getPosition().x + paddleSize.x / 2 &&
				this->pong.ball.getPosition().x - this->pong.ballRadius > left.Paddle.getPosition().x&&
				this->pong.ball.getPosition().y + this->pong.ballRadius >= left.Paddle.getPosition().y - paddleSize.y / 2 &&
				this->pong.ball.getPosition().y - this->pong.ballRadius <= left.Paddle.getPosition().y + paddleSize.y / 2)
			{
				if (this->pong.ball.getPosition().y > this->left.Paddle.getPosition().y)
				{
					ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
					ballSpeed += increase;
				}
				else
				{
					ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
					ballSpeed += increase;
				}
				this->pong.ball.setPosition(this->left.Paddle.getPosition().x + this->pong.ballRadius + paddleSize.x / 2 + 0.1f, this->pong.ball.getPosition().y);
			}

			// Right Paddle
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > this->right.Paddle.getPosition().x - paddleSize.x / 2 &&
				this->pong.ball.getPosition().x + this->pong.ballRadius < this->right.Paddle.getPosition().x &&
				this->pong.ball.getPosition().y + this->pong.ballRadius >= this->right.Paddle.getPosition().y - paddleSize.y / 2 &&
				this->pong.ball.getPosition().y - this->pong.ballRadius <= this->right.Paddle.getPosition().y + paddleSize.y / 2)
			{
				if (this->pong.ball.getPosition().y > this->right.Paddle.getPosition().y)
				{
					ballSpeed += increase;
					ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
				}
				else
				{
					ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
					ballSpeed += increase;
				}

				this->pong.ball.setPosition(this->right.Paddle.getPosition().x - this->pong.ballRadius - paddleSize.x / 2 - 0.1f, this->pong.ball.getPosition().y);
			}
		}
		if (mode == 0)
		{
			float deltaTime = clock.restart().asSeconds();

			// Move the player's paddle

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
				(left.Paddle.getPosition().x - paddleSize.x / 2 > 5.f))
			{
				left.Paddle.move(-paddleSpeed * deltaTime, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
				(left.Paddle.getPosition().x + paddleSize.x / 2 < gameWidth - 5.f))
			{
				left.Paddle.move(paddleSpeed * deltaTime, 0.f);
			}
			/*if (((rightPaddleSpeed < 0.f) && (right.Paddle.getPosition().y - paddleSize.y / 2 > 5.f)) ||
				((rightPaddleSpeed > 0.f) && (right.Paddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f)))
			{
				right.Paddle.move(0.f, rightPaddleSpeed * deltaTime);
			}*/
			//update ai
			/*if (AITimer.getElapsedTime() > AITime)
			{
				AITimer.restart();
				if (pong.ball.getPosition().y + pong.ballRadius > right.Paddle.getPosition().y + paddleSize.y / 2)
					rightPaddleSpeed = paddleSpeed;
				else if (pong.ball.getPosition().y - pong.ballRadius < right.Paddle.getPosition().y - paddleSize.y / 2)
					rightPaddleSpeed = -paddleSpeed;
				else
					rightPaddleSpeed = 0.f;
			}*/
			/*SoundBuffer buffer;
			if (!buffer.loadFromFile("Score.wav")) {
				std::cout << "Error:Loading Sound Effect";
			}
			Sound sound;
			sound.setBuffer(buffer);
			sound.play();*/
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++) {
					if (positionBrick[i][j] != 0)
					{
						int xbrick = 45 + 90 * i;
						int ybrick = 20 + 20 * j;
						//(515 + 30 * j, 30 + 60 * i);
						if ((this->pong.ball.getPosition().x > xbrick - 45) && (this->pong.ball.getPosition().x < xbrick + 45))//o giua ben phai va trai
						{
							//cham duoic gach
							if ((this->pong.ball.getPosition().y + this->pong.ballRadius > ybrick - 10)
								&& ((this->pong.ball.getPosition().y + this->pong.ballRadius < ybrick + 10)))
							{
								ballAngle = pi - ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ball.getPosition().y - 0.1f);
								positionBrick[i][j] = 0;
							}
							//cham tren gach
							if ((this->pong.ball.getPosition().y - this->pong.ballRadius > ybrick - 10)
								&& ((this->pong.ball.getPosition().y - this->pong.ballRadius < ybrick + 10)))
							{
								ballAngle = pi - ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ball.getPosition().y + 0.1f);
								positionBrick[i][j] = 0;
							}
						}
						if ((this->pong.ball.getPosition().y > ybrick - 10) && (this->pong.ball.getPosition().y < ybrick + 10))//o giua tren va duoi
						{
							//cham trai gach
							if ((this->pong.ball.getPosition().x + this->pong.ballRadius > xbrick - 45)
								&& ((this->pong.ball.getPosition().x + this->pong.ballRadius < xbrick + 45)))
							{
								ballAngle = - ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x - 0.1f, this->pong.ball.getPosition().y);
								positionBrick[i][j] = 0;
							}
							//cham phai gach
							if ((this->pong.ball.getPosition().x - this->pong.ballRadius > xbrick - 45)
								&& ((this->pong.ball.getPosition().x - this->pong.ballRadius < xbrick + 45)))
							{
								ballAngle = - ballAngle;
								this->pong.ball.setPosition(this->pong.ball.getPosition().x - 0.1f, this->pong.ball.getPosition().y);
								positionBrick[i][j] = 0;
							}
						}
					}
				}
			}
			// Move the ball
			float factor = ballSpeed * deltaTime;
			this->pong.ball.move(std::sin(ballAngle)* factor, std::cos(ballAngle)* factor);
			// Check collisions between the ball and the screen
			if (this->pong.ball.getPosition().x - this->pong.ballRadius < 0.f)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(this->pong.ballRadius + 0.1f, this->pong.ball.getPosition().y);
			}
			if (this->pong.ball.getPosition().x + this->pong.ballRadius > gameWidth)
			{
				ballAngle = -ballAngle;
				this->pong.ball.setPosition(gameWidth - this->pong.ballRadius + 0.1f, this->pong.ball.getPosition().y);
			}
			if (this->pong.ball.getPosition().y - this->pong.ballRadius < 0.f)
			{
				ballAngle = pi - ballAngle;
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ballRadius + 0.1f);
			}
			if (this->pong.ball.getPosition().y + this->pong.ballRadius > gameHeight)
			{
				isPlaying = false;
				text.message.setString("You lose!\nPress space to restart or\nescape to exit");
				text.message.setFillColor(sf::Color::Blue);
				ballSpeed = 100.f;
				pong.ball.setPosition((float)gameWidth / 2, gameHeight - this->pong.ballRadius - 0.1f);
			}

			// Check the collisions between the ball and the paddles
			// Left Paddle
			if (this->pong.ball.getPosition().x - this->pong.ballRadius <= left.Paddle.getPosition().x + paddleSize.x / 2 &&
				this->pong.ball.getPosition().x - this->pong.ballRadius >= left.Paddle.getPosition().x - paddleSize.x / 2 &&
				this->pong.ball.getPosition().y + this->pong.ballRadius >= left.Paddle.getPosition().y - paddleSize.y / 2 &&
				this->pong.ball.getPosition().y + this->pong.ballRadius <= left.Paddle.getPosition().y + paddleSize.y / 2)
			{
				if (this->pong.ball.getPosition().x > this->left.Paddle.getPosition().x)
				{
					ballSpeed += increase;
					ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
				}
				else
				{
					ballSpeed += increase;
					ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
				}
				pong.ball.setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
				pong.ball.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
				this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->left.Paddle.getPosition().y - this->pong.ballRadius - paddleSize.y / 2 - 0.1f);
			}

			// Right Paddle
			/*if (this->pong.ball.getPosition().x + this->pong.ballRadius > this->right.Paddle.getPosition().x - paddleSize.x / 2 &&
				this->pong.ball.getPosition().x + this->pong.ballRadius < this->right.Paddle.getPosition().x &&
				this->pong.ball.getPosition().y + this->pong.ballRadius >= this->right.Paddle.getPosition().y - paddleSize.y / 2 &&
				this->pong.ball.getPosition().y - this->pong.ballRadius <= this->right.Paddle.getPosition().y + paddleSize.y / 2)
			{
				if (this->pong.ball.getPosition().y > this->right.Paddle.getPosition().y)
				{
					ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
					ballSpeed += increase;
				}
				else
				{
					ballSpeed += increase;
					ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
				}

				this->pong.ball.setPosition(this->right.Paddle.getPosition().x - this->pong.ballRadius - paddleSize.x / 2 - 0.1f, this->pong.ball.getPosition().y);
			}*/
		}

	}

}
void Game::render()
{
	mWindow.clear(sf::Color(238, 232, 170));
	// Draw
	if (isPlaying)
	{
		mWindow.draw(left.Paddle);
		//mWindow.draw(right.Paddle);
		mWindow.draw(pong.ball);
		int level = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (positionBrick[i][j] != 0)
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
					brick.BRICK.setPosition(45 + 90 * i, 20 + 20 * j);
					mWindow.draw(brick.BRICK);
				}
			}
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
			mWindow.draw(text.message);
		}
	}
	// Display things on screen
	mWindow.display();
}
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
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
							left.Paddle.setPosition(gameWidth / 2, 580 + paddleSize.y / 2);
							//left.Paddle.setPosition(10 + paddleSize.x / 2, (float)gameHeight / 2);
							//right.Paddle.setPosition(gameWidth - 10 - paddleSize.x / 2, (float)gameHeight / 2);
							pong.ball.setPosition((float)gameWidth / 2, (float)gameHeight / 2);

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
							left.Paddle.setPosition(10 + paddleSize.x / 2, (float)gameHeight / 2);
							right.Paddle.setPosition(gameWidth - 10 - paddleSize.x / 2, (float)gameHeight / 2);
							pong.ball.setPosition((float)gameWidth / 2, (float)gameHeight / 2);

							// Reset the ball
							do
							{
								ballAngle = (std::rand() % 360) * 2 * pi / 360;
							} while (std::abs(std::cos(ballAngle)) < 0.7f);
						}
						break;
					case 2:
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
					left.Paddle.setPosition(gameWidth / 2, 580 + paddleSize.y / 2);
					pong.ball.setPosition((float)gameWidth / 2, gameHeight - this->pong.ballRadius - 0.1f);
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

