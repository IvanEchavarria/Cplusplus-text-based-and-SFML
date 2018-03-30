#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Ball.h"
#include "Bat.h"



using namespace sf;

class Game: private NonCopyable 
{
private:
	Ball *ball;
	Bat  *bat;
	sf::Text lives;
	sf::Text score;
	sf::Text  mStatistics;
	sf::Time  mStatisticsUpdateTime;
	std::size_t mStatisticsNumFrames;
	int livesCounter;
	int scoreCounter;
	sf::Font mFont;
	sf::Image mIcon;
	sf::Music mMusic;
	RenderWindow window;	
	bool movePlayerLeft;
	bool movePlayerRight;
	bool ballReboundX;
	bool ballReboundY;
	int windowHeight;
	int windowWidth;

	static const sf::Time TimePerFrame;

public:
	Game();
	void ProcessEvents();
	void Render();
	void Run();	
	void update(sf::Time elapsedTime);
	void checkPlayerCollision();
	void checkBallCollision();
	void checkPlayerBallCollision();
	void handlePlayerInput(sf::Keyboard::Key key , bool isPressed);
	void frameUpdateStatistics(sf::Time elapsedTime);

};