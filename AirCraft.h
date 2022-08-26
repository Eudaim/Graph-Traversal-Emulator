#pragma once
#include "Entity.h"

#include "Resources.h"
#include "ResourceHolder.hpp"
class AirCraft : public Entity
{
public:
	typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
	enum Type
	{
		Eagle,
		Raptor,
	};
	AirCraft(Type type, const TextureHolder& textures);
	explicit AirCraft(Textures::ID type, const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	static Textures::ID toTextureID(AirCraft::Type type);

private:
	Type Type;
	sf::Sprite sprite;
};
