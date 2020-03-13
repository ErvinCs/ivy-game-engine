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
		uint16_t EntityIdGenerator;
		uint8_t componentTypeCounter;
		std::map<const char*, std::shared_ptr<BaseComponentContainer>> componentContainers{};
		std::map<const char*, uint8_t> componentTypes{};
		std::vector<Entity> entities{};
		std::set<std::shared_ptr<System>> systems{}; // consider using map with const char* as id
	public:
		~ECS()
		{
			for (auto& it = entities.begin(); it != entities.end(); it++)
			{
				destroyEntity(*it);
			}
			componentTypes.clear();
			componentContainers.clear();
			systems.clear();
			entities.clear();
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
			componentTypes.insert({ typeName, componentTypeCounter });
			// Add a component container for the new type
			componentContainers.insert({ typeName, std::make_shared<ComponentContainer<T>>() });

			componentTypeCounter++;
		}

		template<typename T>
		void addComponent(Entity& entity, T& component)
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
			
			for (auto& it = entities.begin(); it != entities.end(); it++)
			{
				
				if (it->getEntityId() == entity.getEntityId())
				{
					entities.erase(it);
				}
			}
		}

		Entity& createEntity()
		{
			Entity entity = Entity(EntityIdGenerator);
			entities.push_back(entity);
			EntityIdGenerator++;
			return entities.at(entities.size() - 1);
		}

		const std::vector<Entity>& getEntities() {
			return this->entities;
		}

		// Systems
		void addSystem(const std::shared_ptr<System>& system)
		{
			systems.insert(system);
			//systems.emplace(system);
		}


	private:
		template<typename T>
		std::shared_ptr<ComponentContainer<T>> getComponentContainer()
		{
			const char* typeName = typeid(T).name();

			return std::static_pointer_cast<ComponentContainer<T>>(componentContainers[typeName]);
		}	

		ECS()
		{
			EntityIdGenerator = 0;
			componentTypeCounter = 0;
			entities.push_back(Entity(EntityIdGenerator));
			EntityIdGenerator++;
		}

		ECS(const ECS&) = delete;
		ECS& operator=(const ECS&) = delete;
	};
}