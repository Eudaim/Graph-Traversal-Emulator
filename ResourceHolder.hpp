#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Resources.h"
using namespace std;
using namespace sf;

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const string& filename);
	const Resource& get(Identifier id) const;
	Resource& get(Identifier id);
	template<typename Parameter>
	void load(Identifier id, const string& filename, const Parameter& param);
	void loadShape(Identifier id);
	void openFromFile(Identifier id, const string& filename);
private:
	map<Identifier, unique_ptr<Resource>> ResourceMap;
};

//-------------------------------------------------------------------------------------------------------------------------------------
                                                        //Definitions
//-------------------------------------------------------------------------------------------------------------------------------------

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::openFromFile(Identifier id, const string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if(!resource->openFromFile(filename))
	{
		throw std::runtime_error("ResourceHolder::load::Audio - Failed to load Audio" + filename);
	}
	auto insertedIntoMap = ResourceMap.insert(make_pair(id, std::move(resource)));
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	
	if (!resource->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}

	auto insertedIntoMap = ResourceMap.insert(make_pair(id, std::move(resource)));

	//asserting (test?)
	assert(insertedIntoMap.second);

}
template<typename Resource, typename Identifier>
template<typename Parameter>
void ResourceHolder<Resource,Identifier>::load(Identifier id, const string& filename, const Parameter& param)
{
	std::unique_ptr<Resource> resource(new Resource());
	if(!resource->loadFromFile(filename, param))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}

	auto insertedIntoMap = ResourceMap.insert(make_pair(id, std::move(resource)));
}
template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto itr = ResourceMap.find(id);
	return *itr->second;
}
template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto itr = ResourceMap.find(id);
	return *itr->second;
}
template<typename Resource, typename Identifier>
void ResourceHolder<Resource,Identifier>::loadShape(Identifier id)
{
	if(id == Textures::Square)
	{
		std::unique_ptr<Resource> resource(new Resource);
		auto insertedIntoMap = ResourceMap.insert(make_pair(id, std::move(resource)));
	}
}