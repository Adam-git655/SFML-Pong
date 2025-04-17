#include "ball.h"

Ball::Ball(float radius,const sf::Color& fillColor)
{
	shape.setRadius(radius);
    shape.setFillColor(fillColor);
    shape.setOrigin(radius, radius);

}

sf::CircleShape& Ball::getShape()
{
    return shape;
}

sf::Vector2f Ball::getVel() const 
{
    return ballVelocity;
}

float Ball::getSpeed() const
{
    return ballSpeed;
}

void Ball::setVel(const sf::Vector2f& newVel)
{
    ballVelocity = newVel;
}

float Ball::calculate_rand_ball_angle()
{
    std::srand(static_cast<unsigned int>(time(0)));

    int cases = rand() % 4;
    float min_deg = 0.0f;
    float max_deg = 360.0f;

    switch (cases)
    {
    case 0:
        min_deg = 30.0f;
        max_deg = 60.0f;
        break;
    case 1:
        min_deg = 120.0f;
        max_deg = 150.0f;
        break;
    case 2:
        min_deg = 210.0f;
        max_deg = 240.0f;
        break;
    case 3:
        min_deg = 300.0f;
        max_deg = 330.0f;
        break;

    default:
        break;
    }

    float rand_angle_deg = ((float)std::rand() / RAND_MAX) * (max_deg - min_deg) + min_deg;
    float rand_angle = rand_angle_deg * 3.14159f / 180.0f; //in radians

    return rand_angle;
}