#pragma once
#include "ball.h"
#include "paddle.h"

class Game
{
private:
	unsigned int windowWidth;
	unsigned int windowHeight;
	sf::RenderWindow window;
	double deltaTime;
	int playerScore = 0;
	int AIScore = 0;

	Ball ball;
	Paddle paddle;
	Paddle paddleAI;

	sf::Font font;
	sf::Text ScoreTextPlayer;
	sf::Text ScoreTextAI;

public:
	Game(unsigned int wWidth = 1200, unsigned int wHeight = 800);
	void init();
	void run();

	void moveBall();
	void handleInput();
	void movePaddleAI();
	void BallCollisions();
};
