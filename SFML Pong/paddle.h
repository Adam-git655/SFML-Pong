#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Paddle
{
private:
	sf::RectangleShape shape;

	float paddleWidth = 30.0f;
	float paddleHeight = 100.0f;
	float paddleSpeed;

public:
	Paddle(float paddleSpeed = 800.0f, const sf::Color& fillColor = sf::Color::White);

	sf::RectangleShape& getShape();
	float getSpeed();
};