#pragma once

#include <array>
#include <cstdlib>
#include <queue>

#include "Entity.h"
#include "../Core/Logger.h"

class EntityContainer
{
private:
	std::vector<Entity> freeEntities{};
	std::array<Entity, 100> entities{};
	size_t entitiesSize;
public:
	EntityContainer()
	{
		entitiesSize = 0;
	}
	~EntityContainer() = default;

	inline size_t size() { return entitiesSize; }
	inline void incrSize() { entitiesSize++; }
	inline void decrSize() { entitiesSize--; }
	inline std::array<Entity, 100>& array() { return entities; }

	Entity& operator[](std::size_t idx) { return entities[idx]; }
	const Entity& operator[](std::size_t idx) const { return entities[idx]; }

	inline void destroyEntity(Entity& entity)
	{
		IVY_CORE_INFO("EntityContainer: Removing Entity {1}", entity);
		// Efficient Way
		/*for (int i = 0; i < this->entitiesSize; i++)
		{
			if (entities[i] == entity) {
				Entity tempEntity = entities[i];
				entities[i] = entities[entitiesSize - 1];
				entities[entitiesSize - 1] = tempEntity;
				entitiesSize--;
				break;
			}
		}*/

		// User-Friendly Way
		for (int i = 0; i < this->entitiesSize; i++)
		{
			if (entities[i] == entity) 
			{
				addToFreeEntities(entities[i]);
				for (int j = i; j < this->entitiesSize-1; j++)
				{
					entities[j] = entities[j + 1];
				}
				entitiesSize--;
				break;
			}
		}
		
	}

	inline Entity& createEntity()
	{
		Entity entity;
		if (freeEntities.empty())
		{
			entity = (uint16_t)entitiesSize;
		}
		else
		{
			entity = freeEntities.back();
			freeEntities.pop_back();
		}
		entities[entitiesSize] = entity;
		entitiesSize++;
		IVY_CORE_INFO("EntityContainer: Creating Entity {0}. Current number of entities is {1}.", entity, entitiesSize);
		return entities.at(entitiesSize - 1);
	}

	inline auto begin() {
		return entities.begin();
	}

	inline auto end() {
		return entities.begin() + entitiesSize;
	}

	inline const auto cbegin() {
		return entities.cbegin();
	}

	inline const auto cend() {
		return entities.cend() + entitiesSize;
	}

	inline void addToFreeEntities(Entity entity)
	{
		freeEntities.emplace_back(entity);
	}

	inline void addToEntities(uint16_t entity)
	{
		entities[entitiesSize] = entity;
		entitiesSize++;
	}

	inline Entity& getEntity(uint16_t entityId)
	{
		for (int i = 0; i < entitiesSize; i++)
			if (entityId == entities[i])
				return entities[i];
	}

	inline const std::vector<Entity>& getFreeEntities()
	{
		return this->freeEntities;
	}
};
