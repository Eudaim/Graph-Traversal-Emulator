#pragma once
#include <SFML/Graphics.hpp>

#include "Tile.h"
#include <array>

class Grid : private sf::NonCopyable
{
public:
	typedef ResourceHolder<sf::RectangleShape, Textures::ID> ShapeHolder;
	Grid(sf::RenderWindow& window);
	void update();
	void draw();
private:
	void loadShape();
	void buildGrid();
	enum Layer
	{
		BackGround,
		ForeGround,
		LayerCount,
	};
	sf::RenderWindow& window;
	sf::View gridView;
	sf::FloatRect gridBounds;
	SceneNode sceneGraph;
	ShapeHolder myShapes;
	std::array<SceneNode*, LayerCount> sceneLayers;
	sf::Vector2f spawnPosition;
	Tile* tile;
	std::array<array<Tile*, 20>, 20> tiles;
	sf::Thread my_thread;
	sf::Mutex my_mutex;
};
