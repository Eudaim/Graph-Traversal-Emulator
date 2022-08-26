#include "Tile.h"
Tile::Tile(Type type, const ShapeHolder& shapes) : type(type), rectangle(shapes.get(toShapeID(type)))
{
	rectangle.setOrigin(rectangle.getSize().x / 2.f, rectangle.getSize().y / 2.f);
}

void Tile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rectangle, states);
}
Textures::ID Tile::toShapeID(enum Type type)
{
	switch (type)
	{
	case Tile::Square:
			return Textures::Square;
	}

	return Textures::Square;
}
sf::RectangleShape Tile::getRectangle()
{
	return rectangle;
}
