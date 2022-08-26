#include "Grid.h"

#include "SpriteNode.h"

Grid::Grid( sf::RenderWindow& window) :
window(window),
gridView(window.getDefaultView()),
gridBounds(0,0, gridView.getSize().x, gridView.getSize().y),
spawnPosition(gridView.getSize().x / 2.f, gridView.getSize().y / 2),
tile(nullptr),
my_thread(&Grid::update, this)
 {
	loadShape();
	buildGrid();

	gridView.setCenter(spawnPosition);
 }
void Grid::buildGrid()
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(100, 50));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(10, 20);

	window.draw(rectangle);
	for (std::size_t i = 0; i < LayerCount; i++)
	{
		SceneNode::ptr layer(new SceneNode());
		sceneLayers[i] = layer.get();
		sceneGraph.attachChild(std::move(layer));
	}


	std::unique_ptr<Tile> square(new Tile(Tile::Square, myShapes));
	tile = square.get();
	tile->rectangle.setSize(Vector2f(50.f,50.f));
	tile->rectangle.setPosition(0, 0);
	tile->rectangle.setFillColor(sf::Color::Blue);
	sceneLayers[BackGround]->attachChild(std::move(square));

	for(int i = 0; i < tiles.size(); i++)
	{
		for(int j = 0; j < tiles.size(); j++)
		{
			std::unique_ptr<Tile> rect(new Tile(Tile::Square, myShapes));
			tiles[i][j] = rect.get();
			tiles[i][j]->rectangle.setSize(Vector2f(50.f, 50.f));
			tiles[i][j]->rectangle.setPosition(j * 51, i * 51);
			tiles[i][j]->rectangle.setFillColor(sf::Color::Blue);
			sceneLayers[BackGround]->attachChild(std::move(rect));
		}
	}
	

}

void Grid::draw()
{
	window.setView(gridView);
	sf::Lock lock(my_mutex);
	window.draw(sceneGraph);
	my_mutex.unlock();
}
void Grid::loadShape()
{
	myShapes.loadShape(Textures::Square);
}
void Grid::update()
{
	my_thread.launch();
	sf::Lock lock(my_mutex);
	for (int i = 0; i < tiles.size(); i++)
	{
		sf::sleep(sf::milliseconds(20));
		for (int j = 0; j < tiles.size(); j++)
		{
			sf::sleep(sf::milliseconds(20));
			tiles[i][j]->rectangle.setFillColor(sf::Color::Red);
			my_mutex.unlock();
		}
	}

}



