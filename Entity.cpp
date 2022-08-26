#include "Entity.h"

void Entity::setVelocity(sf::Vector2f velocity)
{
	myVelocity = velocity;
}
void Entity::setVelocity(float vX, float vY)
{
	myVelocity = sf::Vector2f(vX, vY);
}
void Entity::updateCurrent(sf::Time dt)
{
	move(myVelocity * dt.asSeconds());
}
sf::Vector2f Entity::getVelocity()
{
	return myVelocity;
}