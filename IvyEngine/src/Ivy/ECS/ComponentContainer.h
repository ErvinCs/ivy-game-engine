#pragma once

#include <array>
#include "Entity.h"
#include "../Exceptions/ComponentNotFoundException.h"

//TODO - Replace array with a more suitable data struct - hash_map  - or don't; idk yet
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
		std::array<T, 100> componentArray{};
		int size;
	public:
		ComponentContainer()
		{
			this->size = 0;
		}
		
		std::array<T, 100>& getComponentArray()
		{
			return this->componentArray;
		}

		int& getSize()
		{
			return this->size;
		}

		void addComponent(Entity& entity, T component) 
		{
			component.setEntityId(entity);
			componentArray[size] = component;
			size++;
		}

		void removeComponent(Entity& entity)
		{

			for (int i = 0; i < size; i++)
			{
				if (componentArray[i].getEntityId() == entity)
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
				if(componentArray[i].getEntityId() == entity)
				{
					return componentArray[i];
				}
			}
			return T();
		}

		void onEntityDestroyed(Entity& entity) override
		{
			removeComponent(entity);
		}
	};
}