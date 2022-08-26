#pragma once
#include <SFML/Graphics.hpp>

#include "SceneNode.h"

class Entity : public SceneNode
{
public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vX, float vY);
	sf::Vector2f getVelocity();
private:
	sf::Vector2f myVelocity;
	virtual void updateCurrent(sf::Time dt) override;
};
