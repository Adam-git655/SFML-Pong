#include "paddle.h"

Paddle::Paddle(float paddleSpeed, const sf::Color& fillColor)
	:paddleSpeed(paddleSpeed)
{
	shape.setSize(sf::Vector2f(paddleWidth, paddleHeight));
	shape.setFillColor(fillColor);
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
}

sf::RectangleShape& Paddle::getShape()
{
	return shape;
}

float Paddle::getSpeed()
{
	return paddleSpeed;
}