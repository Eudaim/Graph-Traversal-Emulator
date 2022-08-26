#pragma once
#include "Entity.h"
#include "ResourceHolder.hpp"
#include "Resources.h"

class Tile : public Entity 
{
public:
	typedef ResourceHolder<sf::RectangleShape, Textures::ID> ShapeHolder; 
	enum Type
	{
		Square,
	};

	Tile(Type type, const ShapeHolder& shapes);
	explicit Tile(Textures::ID, const ShapeHolder& shapes);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::RectangleShape getRectangle();
	Textures::ID toShapeID(enum Type type);

	sf::RectangleShape rectangle;

private:
	Type type;
	sf::IntRect tile;
};
