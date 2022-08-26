#include "AirCraft.h"
AirCraft::AirCraft(enum Type type, const TextureHolder& textures) : Type(type) , sprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void AirCraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
Textures::ID AirCraft::toTextureID(enum Type type)
{
	switch(type)
	{
		case AirCraft::Eagle :
			return Textures::Eagle;
		case AirCraft::Raptor :
			return Textures::Raptor;
	}

	return Textures::Eagle;
}


