#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <array>

#include "AirCraft.h"
#include "SceneNode.h"

class World : private sf::NonCopyable
{
	typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();

private:
	void loadTextures();
	void buildScene();

	enum Layer
	{
		BackGround,
		Air,
		LayerCount,
	};

	sf::RenderWindow& window;
	sf::View worldView;
	TextureHolder myTextures;
	SceneNode sceneGraph;
	std::array<SceneNode*, LayerCount> sceneLayers;

	sf::FloatRect worldBounds;
	sf::Vector2f spawnPosition;
	float scrollSpeed;
	AirCraft* playerAircraft;
	AirCraft* player2Aircraft;


};
