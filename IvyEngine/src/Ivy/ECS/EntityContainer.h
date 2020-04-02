#pragma once

#include <array>
#include <cstdlib>
#include "Entity.h"

class EntityContainer
{
private:
	uint16_t EntityIdGenerator;
	std::array<Entity, 100> entities{};
	size_t entitiesSize;
public:
	EntityContainer()
	{
		EntityIdGenerator = 0;
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
			if (entities[i] == entity) {
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
		Entity entity = EntityIdGenerator;
		entities[entitiesSize] = entity;
		entitiesSize++;
		EntityIdGenerator++;
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
};

