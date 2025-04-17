#include "game.h"

Game::Game(unsigned int wWidth, unsigned int wHeight)
	: windowWidth(wWidth), windowHeight(wHeight),
	paddleAI(250.0f)
{
	window.create(sf::VideoMode(windowWidth, windowHeight), "PONG");
	window.setFramerateLimit(60);
	init();
}

void Game::init()
{
	//Paddle (HUMAN)
	paddle.getShape().setPosition(40.0f, (float)windowHeight / 2);
	
	//Ball
	ball.getShape().setPosition((float)windowWidth / 2, (float)windowHeight / 2);
	sf::Vector2f newballVelocity;
	newballVelocity.x = ball.getSpeed() * cos(ball.calculate_rand_ball_angle());
	newballVelocity.y = ball.getSpeed() * sin(ball.calculate_rand_ball_angle());
	ball.setVel(newballVelocity);

	//Paddle (AI)
	paddleAI.getShape().setPosition(1160.0f, (float)windowHeight / 2);

	//Font
	if (!font.loadFromFile("ARCADECLASSIC.TTF"))
	{
		std::cout << "ERROR LOADING FONT!\n";
	}

	//Score Text Player
	ScoreTextPlayer.setFont(font);
	ScoreTextPlayer.setFillColor(sf::Color::White);
	ScoreTextPlayer.setCharacterSize(100);
	ScoreTextPlayer.setOrigin(ScoreTextPlayer.getLocalBounds().getSize().x / 2, ScoreTextPlayer.getLocalBounds().getSize().y / 2);
	ScoreTextPlayer.setPosition(300.0f, 50.0f);

	//Score Text AI
	ScoreTextAI.setFont(font);
	ScoreTextAI.setFillColor(sf::Color::White);
	ScoreTextAI.setCharacterSize(100);
	ScoreTextAI.setOrigin(ScoreTextAI.getLocalBounds().getSize().x / 2, ScoreTextAI.getLocalBounds().getSize().y / 2);
	ScoreTextAI.setPosition(900.0f, 50.0f);
}

void Game::run()
{
	sf::Clock clock;
	double lastTime = clock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		double currentTime = clock.getElapsedTime().asSeconds();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		ScoreTextPlayer.setString(std::to_string(playerScore));
		ScoreTextAI.setString(std::to_string(AIScore));

		handleInput();
		moveBall();
		movePaddleAI();
		BallCollisions();

		window.clear();
		window.draw(ScoreTextPlayer);
		window.draw(ScoreTextAI);
		window.draw(paddle.getShape());
		window.draw(ball.getShape());
		window.draw(paddleAI.getShape());
		window.display();
	}
}

void Game::handleInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.scancode == sf::Keyboard::Scan::W)
			{
				paddle.getShape().move(0.0f, -paddle.getSpeed() * deltaTime);
			}

			if (event.key.scancode == sf::Keyboard::Scan::S)
			{
				paddle.getShape().move(0.0f, paddle.getSpeed() * deltaTime);
			}
		}
	}
}

void Game::moveBall()
{
	ball.getShape().move(ball.getVel().x * deltaTime, ball.getVel().y * deltaTime);

	sf::Vector2f ballPos = ball.getShape().getPosition();
	sf::Vector2f ballVel = ball.getVel();


	if (ballPos.y - ball.getShape().getRadius() <= 0 || 
		ballPos.y + ball.getShape().getRadius() >= windowHeight)
	{
		ballVel.y *= -1;
	}

	if (ballPos.x <= 0)
	{
		AIScore += 1;
		ball.getShape().setPosition((float)windowWidth / 2, (float)windowHeight / 2);
		ballVel.x = ball.getSpeed() * cos(ball.calculate_rand_ball_angle());
		ballVel.y = ball.getSpeed() * sin(ball.calculate_rand_ball_angle());
	}
	if (ballPos.x >= windowWidth)
	{
		playerScore += 1;
		ball.getShape().setPosition((float)windowWidth / 2, (float)windowHeight / 2);
		ballVel.x = ball.getSpeed() * cos(ball.calculate_rand_ball_angle());
		ballVel.y = ball.getSpeed() * sin(ball.calculate_rand_ball_angle());
	}

	ball.setVel(ballVel);
}

void Game::movePaddleAI()
{
	if (paddleAI.getShape().getPosition().y < ball.getShape().getPosition().y)
	{
		paddleAI.getShape().move(0.0f, paddleAI.getSpeed() * deltaTime);
	}
	if (paddleAI.getShape().getPosition().y > ball.getShape().getPosition().y)
	{
		paddleAI.getShape().move(0.0f, -paddleAI.getSpeed() * deltaTime);
	}
}

void Game::BallCollisions()
{
	sf::Vector2f ballPos = ball.getShape().getPosition();
	sf::Vector2f ballVel = ball.getVel();

	//Human Paddle Collision
	sf::Vector2f paddlePos = paddle.getShape().getPosition();

	float total_x = ball.getShape().getRadius() + paddle.getShape().getSize().x / 2;
	float dist_x = abs(ballPos.x - paddlePos.x);

	float total_y = ball.getShape().getRadius() + paddle.getShape().getSize().y / 2;
	float dist_y = abs(ballPos.y - paddlePos.y);

	if (dist_x <= total_x && dist_y <= total_y)
	{
		float overlap_x = total_x - dist_x;
		float overlap_y = total_y - dist_y;
		if (overlap_x < overlap_y)
		{
			if (ballPos.x < paddlePos.x)
			{
				ball.getShape().setPosition(ballPos.x - overlap_x - 1.0f, ballPos.y);
			}
			else
			{
				ball.getShape().setPosition(ballPos.x + overlap_x + 1.0f, ballPos.y);
			}
			
			ballVel.x *= -1;
		}
		else
		{
			if (ballPos.y < paddlePos.y)
			{
				ball.getShape().setPosition(ballPos.x, ballPos.y - overlap_y);
			}
			else
			{
				ball.getShape().setPosition(ballPos.x, ballPos.y + overlap_y);
			}

			ballVel.y *= -1;
		}

		ball.setVel(ballVel);

	}

	//AI Paddle Collisions
	sf::Vector2f paddleAIPos = paddleAI.getShape().getPosition();

	total_x = ball.getShape().getRadius() + paddleAI.getShape().getSize().x / 2;
	dist_x = abs(ballPos.x - paddleAIPos.x);

	total_y = ball.getShape().getRadius() + paddleAI.getShape().getSize().y / 2;
	dist_y = abs(ballPos.y - paddleAIPos.y);

	if (dist_x <= total_x && dist_y <= total_y)
	{
		float overlap_x = total_x - dist_x;
		float overlap_y = total_y - dist_y;
		if (overlap_x < overlap_y)
		{
			if (ballPos.x < paddleAIPos.x)
			{
				ball.getShape().setPosition(ballPos.x - overlap_x - 1.0f, ballPos.y);
			}
			else
			{
				ball.getShape().setPosition(ballPos.x + overlap_x + 1.0f, ballPos.y);
			}

			ballVel.x *= -1;
		}
		else
		{
			if (ballPos.y < paddleAIPos.y)
			{
				ball.getShape().setPosition(ballPos.x, ballPos.y - overlap_y);
			}
			else
			{
				ball.getShape().setPosition(ballPos.x, ballPos.y + overlap_y);
			}

			ballVel.y *= -1;
		}

		ball.setVel(ballVel);

	}

}