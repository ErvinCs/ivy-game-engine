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
		std::map<const char*, std::shared_ptr<BaseComponentContainer>> componentContainers;
		std::map<const char*, uint8_t> componentTypes;
		std::queue<Entity*> entities;
		std::vector<System*> systems; // consider using map with const char* as id
	public:
		ECS();
		~ECS();

		// Components
		template<typename T>
		void addComponentType()
		{
			const char* typeName = typeid(T).name();

			componentTypes.insert({typeName, /*TODO - way to get type ID & define all types somewhere*/})
		}

		template<typename T>
		void addComponent(Entity entity, T component)
		{
			getComponentContainer<T>()->addComponent(entity, component);
		}

		template<typename T>
		void removeComponent(Entity entity)
		{
			getComponentContainer<T>()->removeComponent(entity);
		}

		template<typename T>
		T& getComponent(Entity entity)
		{
			getComponentContainer<T>()->getComponent(entity);
		}

		// Entities
		void destroyEntity(Entity entity)
		{
			for (auto const& container : componentContainers)
			{
				auto const& component = container.second;

				component->onEntityDestroyed(entity);
			}
			// TODO - Separate live entities from dead entities
			// TODO - Destroy entity
		}

		Entity createEntity()
		{
			// TODO
		}

		// Systems
		void addSystem(System* system)
		{
			systems.push_back(system);
		}


	private:
		template<typename T>
		std::shared_ptr<ComponentContainer<T>> getComponentContainer()
		{
			const char* typeName = typeid(T).name();

			return std::static_pointer_cast<ComponentContainer<T>>(componentContainers[typeName]);
		}
	};

}