#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Grid.h"
#include "World.h"
class Game
{
public:
	Game();
	void run();

private:
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	const float PlayerMovementSpeed = 100.f;

	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	bool mIsMovingUp, mIsMovingDown, mIsMovingRight, mIsMovingLeft;

	sf::RenderWindow mWindow;

	World world;
	Grid  grid;

};