#pragma once

#include <map>
#include <queue>
#include <vector>
#include <stdint.h>

#include "Component.h"
#include "ComponentContainer.h"
#include "Entity.h"
#include "System.h"

namespace Ivy {

	class ECS
	{
	private:
		static uint16_t EntityIdGenerator;
		static uint8_t componentTypeCounter;
		std::map<const char*, std::shared_ptr<BaseComponentContainer>> componentContainers;
		std::map<const char*, uint8_t> componentTypes;
		//std::set<Entity> entities;
		//std::set<System*> systems; // consider using map with const char* as id
	public:
		ECS() 
		{ 
			EntityIdGenerator = 0; 
			componentTypeCounter = 0;
		}

		~ECS()
		{
			//for (auto it : entities)
			//{
			//	destroyEntity(it);
			//}
		}

		static ECS& getInstance()
		{
			static ECS instance{};
			return instance;
		}

		// Components
		template<typename T>
		void addComponentType()
		{
			const char* typeName = typeid(T).name();

			// Add a new component type
			componentTypes.insert({typeName, componentTypeCounter })
			// Add a component container for the new type
			componentContainers.insert({ typeName, std::make_shared<ComponentContainer<T>> });

			componentTypeCounter++;
		}

		template<typename T>
		void addComponent(Entity& entity, const T& component)
		{
			getComponentContainer<T>()->addComponent(entity, component);
		}

		template<typename T>
		void removeComponent(Entity& entity)
		{
			getComponentContainer<T>()->removeComponent(entity);
		}

		template<typename T>
		T& getComponent(Entity& entity)
		{
			return getComponentContainer<T>()->getComponent(entity);
		}

		// Entities
		void destroyEntity(Entity& entity)
		{
			for (auto const& container : componentContainers)
			{
				auto const& component = container.second;

				component->onEntityDestroyed(entity);
			}
			// TODO - Separate live entities from dead entities
			//entities.erase(entity);
		}

		Entity& createEntity()
		{
			Entity* entity = new Entity(EntityIdGenerator);
			EntityIdGenerator++;
			//this->entities.emplace(*entity);
			return *entity;
		}

		// Systems
		void addSystem(System& system)
		{
			//systems.emplace(system);
		}


	private:
		template<typename T>
		std::shared_ptr<ComponentContainer<T>> getComponentContainer()
		{
			const char* typeName = typeid(T).name();

			return std::static_pointer_cast<ComponentContainer<T>>(componentContainers[typeName]);
		}	
		ECS(const ECS&) = delete;
		ECS& operator=(const ECS&) = delete;
	};
}