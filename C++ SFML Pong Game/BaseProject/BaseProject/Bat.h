#pragma once
#include <SFML/Graphics.hpp>

class Bat
{
private:
	sf::RectangleShape batShape;
	float			   batSpeed;

public:
	Bat(sf::Vector2f size, sf::Vector2f position, float speed, sf::Color color);
	sf::Vector2f getPosition();
	sf::RectangleShape getShape();
	void setPosition(float x);
	void moveLeft(float seconds);
	void moveRight(float seconds);
	void Update(sf::Time deltaTime , bool leftPressed, bool rightPressed);
	
};

