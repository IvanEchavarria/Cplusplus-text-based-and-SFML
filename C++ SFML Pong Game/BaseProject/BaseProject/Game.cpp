#include "Game.h"

//using namespace sf;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	{
		window.create(VideoMode(800, 600), "Echavarria Ivan, Assignment 1");

		//Load font from file
		if (!mFont.loadFromFile("Media/Sonicxb.ttf"))
		{
			return;
		}
		lives.setFont(mFont);
		score.setFont(mFont);
		mStatistics.setFont(mFont);

		//Text location on the screen
		lives.setPosition(50.0f, 0.0f);
		score.setPosition(200.0f, 0.0f);
		mStatistics.setPosition(600.0f, 0.0f);

		//Color and number of characters in the text
		lives.setCharacterSize(20);
		score.setCharacterSize(20);
		mStatistics.setCharacterSize(14);
		
		lives.setFillColor(sf::Color::Black);
		score.setFillColor(sf::Color::Black);
		mStatistics.setFillColor(sf::Color::Black);

		//Set default text for lives and score
		livesCounter = 5;
		scoreCounter = 0;
		lives.setString("Lives: " + std::to_string(livesCounter));
		score.setString("Score: " + std::to_string(scoreCounter));
		mStatistics.setString("Statistics");

		ball = new Ball(15.0f, 200.0f, 200.0f, sf::Color::Blue);
		bat = new Bat(sf::Vector2f(100.0f, 25.0f),sf::Vector2f( window.getSize().x * 0.50f - 50.0f, window.getSize().y - 100.f), 200.0f , sf::Color::Green);
		movePlayerLeft = false;
		movePlayerRight = false;
		ballReboundX = false;
		ballReboundY = false;		
	}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;			
			ProcessEvents();
			update(TimePerFrame);			
		}

		frameUpdateStatistics(elapsedTime);
		Render();
	}

}


void Game::ProcessEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			//Handle player input here
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			//Handle player input here
			handlePlayerInput(event.key.code, false);
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key,  bool isPressed)
{
	if (key == sf::Keyboard::A) //Move left
	{
		movePlayerLeft = isPressed;
	}
	else if (key == sf::Keyboard::D) // Move Right
	{
		movePlayerRight = isPressed;
	}
}

void Game::update(sf::Time elapsedTime)
{
	// check if the player is colliding with the ball
	checkPlayerBallCollision();

	//check PlayerPosition againts bounds
	checkPlayerCollision();

	//Update player Position
	bat->Update(elapsedTime, movePlayerLeft, movePlayerRight);

	//check ball position againts bounds
	checkBallCollision();

	// check if the player is colliding with the ball
	checkPlayerBallCollision();

	//Update ball position
	ball->Update(elapsedTime, ballReboundX, ballReboundY);
}

void Game::checkPlayerBallCollision()
{
	// check if within the player x bounds
	if (ball->getPosition().x >= bat->getPosition().x && (ball->getPosition().x <= (bat->getPosition().x + bat->getShape().getSize().x)))
	{
		//check if we are touching the player at y position
		if ((ball->getPosition().y + ball->getshape().getRadius() * 2 >= bat->getPosition().y) && 

			ball->getPosition().y + ball->getshape().getRadius() * 2 <= (bat->getPosition().y + (bat->getShape().getSize().y/2)))
		{
			scoreCounter += 10;
			score.setString("Score: " + std::to_string(scoreCounter));
			ballReboundY = true;
		}
	}
}

void Game::checkPlayerCollision()
{
	//Check window collision for player
	if ((bat->getPosition().x) <= (window.getSize().x - window.getSize().x)) // check if we are within left bounds
	{
		bat->setPosition(0.0f); // if less than the screen size then set it to the screen left bounds
		movePlayerLeft = false;
	}
	if (bat->getPosition().x >= window.getSize().x - bat->getShape().getSize().x) // Check if within right bounds
	{
		bat->setPosition(window.getSize().x - bat->getShape().getSize().x); // if greater than the screen size then set it to the right bounds - size of the shape
		movePlayerRight = false;
	}
}

void Game::checkBallCollision()
{
	//Check Collision with window and player
	//Check X Collision
	if (ball->getPosition().x <= 0.f || ball->getPosition().x >= window.getSize().x - ball->getshape().getRadius() * 2)
	{
		ballReboundX = true;
	}
	else
	{
		ballReboundX = false;
	}
	//Check Y Collision
	if (ball->getPosition().y <= 0.f)
	{
		ballReboundY = true;
	}
	else
	{
		ballReboundY = false;
	}	
	if (ball->getPosition().y >= window.getSize().y)
	{
		livesCounter--;
		lives.setString("Lives: " + std::to_string(livesCounter));
		ball->setPosition(200.0f, 200.0f);
		ballReboundY = false;
	}
}

void Game::frameUpdateStatistics(sf::Time elapsedTime)
{
	
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatistics.setString("Frames/Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
						      "Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + " us");
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::Render()
{
	window.clear(sf::Color(255, 215, 0, 255));
	window.draw(ball->getshape());
	window.draw(bat->getShape());
	window.draw(lives);
	window.draw(score);
	window.draw(mStatistics);
	window.display();
}



