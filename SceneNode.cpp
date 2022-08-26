#include "SceneNode.h"

#include <cassert>

SceneNode::SceneNode()
{
	Parent = nullptr; 
}


void SceneNode::attachChild(ptr child)
{

	child->Parent = this;													 //set the parent node for the child class
	Children.push_back(std::move(child));								//add the Child node to vector of Children node so that the parent class can keep track of it
}

SceneNode::ptr SceneNode::detachChild(const SceneNode& node)
{
	ptr result; 
	auto found = std::find_if(Children.begin(), Children.end(), [&](ptr& p) -> bool {return p.get() == &node; });
	assert(found != Children.end());
	result = std::move(*found);
	result->Parent = nullptr; 
	Children.erase(found);
	return result;
}
void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = states.transform * getTransform();
	drawCurrent(target, states);
	for(auto itr = Children.begin(); itr != Children.end(); itr++)
	{
		(*itr)->draw(target, states); 
	}
}
void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (auto child = Children.begin(); child != Children.end(); child++)
	{
		(*child)->update(dt);
	}
}
sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for(const SceneNode* node = this; node != nullptr; node = node->Parent)
	{
		transform = node->getTransform() * transform; 
	}

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

void SceneNode::updateCurrent(sf::Time dt)
{
	
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	
}
