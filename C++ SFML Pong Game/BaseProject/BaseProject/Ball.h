#pragma once
#include <SFML/Graphics.hpp>


class Ball
{

private:
	sf::CircleShape ballShape;	
	sf::Vector2f    position;
	float		xVelocity;
	float		yVelocity;

public:
	Ball(float radius, float posX, float posY, sf::Color color);
	sf:: Vector2f getPosition();
	void Ball::setPosition(float x , float y);
	sf::CircleShape getshape();
	void Update(sf::Time deltaTime, bool xRebound, bool yRebound);

	
};

