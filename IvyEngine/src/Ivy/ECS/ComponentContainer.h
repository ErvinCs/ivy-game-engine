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
		//int capacity = 100;	//MAX ENTITIES
		std::array<T, 3> componentArray{};
		int size;
	public:
		ComponentContainer()
		{
			this->size = 0;
		}

		/*ComponentContainer(const ComponentContainer& container)
		{
			this->componentArray = container.getComponentArray();
			this->size = container.getSize();
		}
		ComponentContainer(ComponentContainer&& container) = default;
		ComponentContainer& operator=(ComponentContainer&& container) = default;
		ComponentContainer& operator=(const ComponentContainer& container) = default;*/
		
		std::array<T, 100>& getComponentArray()
		{
			return this->componentArray;
		}

		int& getSize()
		{
			return this->size;
		}

		void addComponent(Entity& entity, T& component) 
		{
			//entity.addComponent(&component);
			component.setEntityId(entity.getEntityId());
			componentArray[size] = component;
			size++;
		}

		void removeComponent(Entity& entity)
		{

			for (int i = 0; i < size; i++)
			{
				if (componentArray[i].getEntityId() == entity.getEntityId())
				{
					T tempComponent = componentArray[i];
					componentArray[i] = componentArray[size - 1];
					componentArray[size - 1] = tempComponent;
					size--;

					// WORK ON THIS
					//entity.removeComponent(&tempComponent);
				}
			}
		}

		T& getComponent(Entity& entity)
		{
			for (int i = 0; i < size; i++)
			{
				if (componentArray[i].getEntityId() == entity.getEntityId())
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