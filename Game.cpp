#include "Game.h"

#include <functional>

Game::Game() :
	mWindow(sf::VideoMode(1020, 1020), "SFML Application"),
	world(mWindow),
	grid(mWindow)
{
	
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	std::thread my_thread(&Game::update, this, this->TimePerFrame);
	while(mWindow.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while(timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame); 
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed :
				handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased :
				handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::Closed :
				mWindow.close();
				break;
		}
	}
}
void Game::update(sf::Time deltaTime)
{
	
	world.update(deltaTime);
	grid.update();
}
void Game::render()
{
	mWindow.setView(mWindow.getDefaultView());
	mWindow.clear();
	world.draw();
	grid.draw();
	mWindow.display(); 
}
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if(key == sf::Keyboard::W)
	{
		mIsMovingUp = isPressed;
	}
	else if(key == sf::Keyboard::S)
	{
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::D)
	{
		mIsMovingRight = isPressed; 
	}
	else if (key == sf::Keyboard::A)
	{
		mIsMovingLeft = isPressed;
	}
}
