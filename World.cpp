#include "World.h"

#include "SpriteNode.h"

World::World(sf::RenderWindow& window) :
window(window),
worldView(window.getDefaultView()),
worldBounds(0.f, 0.f, worldView.getSize().x, 10000000.f),
spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y),
scrollSpeed(-1100.f),
playerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	worldView.setCenter(spawnPosition);
	
}
void World::loadTextures()
{
	myTextures.load(Textures::Eagle, "C:/Users/Ardon/OneDrive/Desktop/SFML-Game-Development-Book-master/SFML-Game-Development-Book-master/03_World/Media/Textures/Eagle.png");
	myTextures.load(Textures::Raptor, "C:/Users/Ardon/OneDrive/Desktop/SFML-Game-Development-Book-master/SFML-Game-Development-Book-master/03_World/Media/Textures/Raptor.png");
	myTextures.load(Textures::Desert, "C:/Users/Ardon/OneDrive/Desktop/SFML-Game-Development-Book-master/SFML-Game-Development-Book-master/03_World/Media/Textures/Desert.png");
}
void World::buildScene()
{
	for(std::size_t i = 0; i < LayerCount; i++)
	{
		SceneNode::ptr layer(new SceneNode());
		sceneLayers[i] = layer.get();

		sceneGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = myTextures.get(Textures::Desert);
	sf::IntRect textureRect(worldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[BackGround]->attachChild(std::move(backgroundSprite));

	std::unique_ptr<AirCraft> leader(new AirCraft(AirCraft::Eagle, myTextures));
	playerAircraft = leader.get();
	playerAircraft->setPosition(spawnPosition);
	playerAircraft->setVelocity(40.f, scrollSpeed);
	sceneLayers[Air]->attachChild(std::move(leader));

	std::unique_ptr<AirCraft> follow(new AirCraft(AirCraft::Eagle, myTextures));
	player2Aircraft = follow.get();
	player2Aircraft->setPosition(spawnPosition.x, spawnPosition.y - 100.f);
	player2Aircraft->setVelocity(0.f, scrollSpeed);
	sceneLayers[Air]->attachChild(std::move(follow));

	std::unique_ptr<AirCraft> leftEscort(new AirCraft(AirCraft::Raptor, myTextures));
	leftEscort->setPosition(-80.f, 50.f);
	playerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<AirCraft> rightEscort(new AirCraft(AirCraft::Raptor, myTextures));
	rightEscort->setPosition(80.f, 50.f);
	playerAircraft->attachChild(std::move(rightEscort));

	
}
void World::draw()
{
	window.setView(worldView);
	window.draw(sceneGraph);
}
void World::update(sf::Time dt)
{
	worldView.move(0.f, scrollSpeed * dt.asSeconds());

	sf::Vector2f position = playerAircraft->getPosition();
	sf::Vector2f velocity = playerAircraft->getVelocity();

	if(position.x <= worldBounds.left + 150 || position.x >= worldBounds.left + worldBounds.width - 150)
	{
		velocity.x = -velocity.x;
		playerAircraft->setVelocity(velocity);
	}

	sceneGraph.update(dt);
}