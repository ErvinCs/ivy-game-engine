#pragma once

#include <array>
#include "Entity.h"

//TODO - Replace array with hash_map
namespace Ivy {

	class BaseComponentContainer
	{
	public:
		virtual ~BaseComponentContainer() = default;
		virtual void onEntityDestroyed(Entity entity) = 0;
	};

	template<typename T>
	class ComponentContainer : public BaseComponentContainer
	{
	private:
		int capacity = 1000;	//MAX ENTITIES
		std::array<T, capacity> componentArray;
		int size = 0;
	public:
		ComponentContainer() = default;

		void addComponent(Entity entity, T component) 
		{
			entity.addComponent(component&);
			componentArray[size] = component;
			size++;
		}

		void removeComponent(Entity entity)
		{
			for (int i = 0; i < size; i++)
			{
				if (componentArray[i].getComponentId() == entity.getEntityId())
				{
					componentArray.swap(i, size - 1);
					size--;
				}
			}
		}

		T& getComponent(Entity entity)
		{
			for (int i = 0; i < size; i++)
			{
				if (componentArray[i].getComponentId() == entity.getEntityId())
				{
					return componentArray[i];
				}
			}
			// TODO - throw error
			return nullptr;
		}

		void onEntityDestroyed(Entity entity) override
		{
			removeComponent(entity);
		}
	};
}