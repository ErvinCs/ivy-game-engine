#pragma once

#include <array>
#include "Entity.h"
#include "../Exceptions/ComponentNotFoundException.h"

//TODO - Replace array with hash_map
namespace Ivy {

	class BaseComponentContainer
	{
	public:
		virtual ~BaseComponentContainer() = default;
		virtual void onEntityDestroyed(Entity& entity) = 0;
	};

	template<typename T>
	class ComponentContainer : public BaseComponentContainer
	{
	private:
		//int capacity = 1000;	//MAX ENTITIES
		std::array<T, 1000> componentArray;
		int size = 0;
	public:
		ComponentContainer() = default;

		void addComponent(Entity& entity, const T& component) 
		{
			entity.addComponent(std::make_shared<T>(component));
			componentArray[size] = component;
			size++;
		}

		void removeComponent(Entity& entity)
		{

			for (int i = 0; i < size; i++)
			{
				if (componentArray[i].getComponentId() == entity.getEntityId())
				{
					T tempComponent = componentArray[i];
					componentArray[i] = componentArray[size - 1];
					componentArray[size - 1] = tempComponent;
					size--;
				}
			}
		}

		T& getComponent(Entity& entity)
		{
			for (int i = 0; i < size; i++)
			{
				if (componentArray[i].getComponentId() == entity.getEntityId())
				{
					return componentArray[i];
				}
			}
			throw new ComponentNotFoundException("Could not find a component of the given type!");
		}

		void onEntityDestroyed(Entity& entity) override
		{
			removeComponent(entity);
		}
	};
}