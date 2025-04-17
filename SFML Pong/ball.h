#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>

class Ball
{
private:
	sf::CircleShape shape;
	float ballSpeed = 400.0f;
	sf::Vector2f ballVelocity;

public:
	Ball(float radius = 15.0f, const sf::Color& fillColor = sf::Color::Red);
	float calculate_rand_ball_angle();

	sf::CircleShape& getShape();
	sf::Vector2f getVel() const;
	float getSpeed() const;

	void setVel(const sf::Vector2f& newVel);
};