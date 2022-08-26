# pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> ptr;

public:
	SceneNode();
	void attachChild(ptr child);
	void update(sf::Time dt);
	ptr detachChild(const SceneNode& node);
	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;								//draw the entire scene node (including childrens)
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;						//draw just the current node
	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);
	std::vector<ptr> Children;
	SceneNode* Parent;
};
