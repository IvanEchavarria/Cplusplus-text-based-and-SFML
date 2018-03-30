#include "Bat.h"



Bat::Bat(sf::Vector2f size, sf::Vector2f position, float speed, sf::Color color)
{
	batShape.setSize(size);
	batShape.setPosition(position);
	batSpeed = speed;
	batShape.setFillColor(color);
}

sf::Vector2f Bat::getPosition()
{	
	return batShape.getPosition();
}

void Bat::setPosition(float x)
{
	batShape.setPosition(sf::Vector2f(x,batShape.getPosition().y));
}

sf::RectangleShape Bat::getShape()
{
	return batShape;
}



void Bat::Update(sf::Time deltaTime, bool leftPressed, bool rightPressed)
{
		
	if (leftPressed && !rightPressed)
	{
		moveLeft(deltaTime.asSeconds());
	}

	if (rightPressed && !leftPressed)
	{
		moveRight(deltaTime.asSeconds());
	}

}

void Bat::moveLeft(float seconds)
{
	//Move adds the offset values in the vector 2 to the current position of the object (ie. pos x is 100. batpeed -10. then 100 -10 = 90; moves 10 units to the left)
	batShape.move(sf::Vector2f(-batSpeed * seconds, 0.0f ));
}
void Bat::moveRight(float seconds)
{
	batShape.move(sf::Vector2f(batSpeed * seconds, 0.0f));
}