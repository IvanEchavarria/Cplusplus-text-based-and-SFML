#include "Ball.h"



Ball::Ball(float radius, float posX, float posY, sf::Color color)
{
	ballShape.setRadius(radius);
	position = sf::Vector2f(posX, posY);
	ballShape.setPosition(position);
	ballShape.setFillColor(color);
	xVelocity = 220.5f;
	yVelocity = 220.5f;
}

sf::Vector2f Ball::getPosition()
{
	return ballShape.getPosition();
}

void Ball::setPosition(float x, float y)
{
	ballShape.setPosition(sf::Vector2f(x, y));
}

sf::CircleShape Ball::getshape()
{
	return ballShape;
}


void Ball::Update(sf::Time deltaTime, bool xRebound, bool yRebound)
{
	if (xRebound)
	{
		xVelocity *= -1;
	}

	if (yRebound)
	{
		yVelocity *= -1;
	}

	ballShape.move(sf::Vector2f(xVelocity, yVelocity) * deltaTime.asSeconds());

}

