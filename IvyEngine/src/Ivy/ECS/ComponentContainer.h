#pragma once

#include <array>
#include "Entity.h"
#include "../Exceptions/ComponentNotFoundException.h"

//TODO - Replace array with a more suitable data struct - hash_map 
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
		std::array<T, 1000> componentArray{};
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

		void addComponent(Entity& entity, T& component) 
		{
			//component.setEntityId(entity.getEntityId());
			component.setEntityId(entity);
			componentArray[size] = component;
			size++;
		}

		void removeComponent(Entity& entity)
		{

			for (int i = 0; i < size; i++)
			{
				if (componentArray[i].getEntityId() == entity)
				//if (componentArray[i].getEntityId() == entity.getEntityId())
				{
					//componentArray[i].setEntityId(-1);

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
				//if (componentArray[i].getEntityId() == entity.getEntityId())
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