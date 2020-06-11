#pragma once

#include <array>
#include <cstdlib>
#include <unordered_set>

#include "Entity.h"
#include "../Core/Logger.h"

namespace Ivy
{
	/**
	 * Contains all the Entity instances.
	 * The `entities` packed-array contains all active entities.
	 * The `freeEntities` set keeps track of used and deleted entities such that they can be added back into the application.
	 */
	class EntityContainer
	{
	private:
		// A set of entities that were removed. When adding a new entity this set is queried first
		std::unordered_set<Entity> freeEntities{};
		// The pre-allocated array of entities
		std::array<Entity, MAX_Entities> entities{};
		// The number of active entities
		size_t entitiesSize;
	public:

		/**
		 * Creates an empty entity container with size 0.
		 */
		EntityContainer()
		{
			entitiesSize = 0;
		}
		~EntityContainer() = default;

		inline size_t size() { return entitiesSize; }
		inline void incrSize() { entitiesSize++; }
		inline void decrSize() { entitiesSize--; }
		inline std::array<Entity, MAX_Entities>& array() { return entities; }

		[[DEPRECATED]]
		Entity& operator[](std::size_t idx) { return entities[idx]; }
		[[DEPRECATED]]
		const Entity& operator[](std::size_t idx) const { return entities[idx]; }

		/**
		 * @returns Entity at `index` index in the container array
		 */
		Entity* at(int index) { return &entities[index]; }

		/**
		 * Moves the entity from the `entities` array to the `freeEntities` set
		 */
		inline void destroyEntity(Entity& entity)
		{
			IVY_CORE_INFO("EntityContainer: Removing Entity {0}", entity);
			for (int i = 0; i < this->entitiesSize; i++)
			{
				if (entities[i] == entity)
				{
					addToFreeEntities(entities[i]);
					for (int j = i; j < this->entitiesSize - 1; j++)
					{
						entities[j] = entities[j + 1];
					}
					entitiesSize--;
					break;
				}
			}

		}

		/**
		 * Adds an entity to the `entities` array.
		 * If the `freeEntities` set is not empty then it pops an entity from it.
		 * Otherwise it creates a new Entity identified by the index in the array.
		 * @returns Entity that was created
		 */
		inline Entity& createEntity()
		{
			Entity entity;
			if (freeEntities.empty())
			{
				entity = (uint16_t)entitiesSize;
			}
			else
			{
				entity = *freeEntities.begin();
				freeEntities.erase(freeEntities.begin());
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

		/**
		 * Adds `entity` to the `freeEntities` set
		 */
		inline void addToFreeEntities(Entity entity)
		{
			freeEntities.emplace(entity);
		}

		/**
		 * Adds `entity` to the `entities` array
		 */
		inline void addToEntities(uint16_t entity)
		{
			entities[entitiesSize] = entity;
			entitiesSize++;
		}

		/**
		 * @returns Entity& a reference in the `entities` array to the entity equal to `entityId`
		 */
		inline Entity& getEntity(uint16_t entityId)
		{
			for (int i = 0; i < entitiesSize; i++)
				if (entityId == entities[i])
					return entities[i];
		}

		/**
		 * @returns unordered_set<Entity>& containing the entities that were destroyed and removed from the set of entities
		 */
		inline const std::unordered_set<Entity>& getFreeEntities()
		{
			return this->freeEntities;
		}

		/**
		 * Destroys all the entities and adds them to `freeEntities`
		 */
		inline void clearEntities()
		{
			while (entitiesSize > 0)
			{
				addToFreeEntities(entities[entitiesSize]);
				entitiesSize--;
			}
		}
	};

}