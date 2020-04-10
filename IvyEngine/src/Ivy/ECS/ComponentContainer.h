#pragma once

#include <array>
#include "Entity.h"
#include "../Exceptions/ComponentNotFoundException.h"
#include "../Core/Logger.h"

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
		std::array<T, MAX_Entities> componentArray{};
		int size;
	public:
		ComponentContainer()
		{
			this->size = 0;
			// Log produces error

			//IVY_CORE_INFO("ComponentContainer: Constructing ComponentContainer: type={0}", typeid(T).name());
		}
		
		std::array<T, MAX_Entities>& getComponentArray()
		{
			return this->componentArray;
		}

		int& getSize()
		{
			return this->size;
		}

		void addComponent(Entity& entity, T component) 
		{
			IVY_CORE_INFO("ComponentContainer: Adding Component {0} to Entity {1}", typeid(T).name(), entity);
			component.setEntityId(entity);
			componentArray[size] = component;
			size++;

		}

		void removeComponent(Entity& entity)
		{
			IVY_CORE_INFO("ComponentContainer: Removing Component {0} from Entity {1}", typeid(T).name(), entity);
			for (int i = 0; i < size; i++)
			{
				if (componentArray[i].getEntityId() == entity)
				{
					T tempComponent = componentArray[i];
					componentArray[i] = componentArray[size - 1];
					componentArray[size - 1] = tempComponent;
					size--;
					break;
				}
			}
		}

		T& getComponent(Entity& entity)
		{
			for (int i = 0; i < size; i++)
			{
				if(componentArray[i].getEntityId() == entity)
				{
					//IVY_CORE_INFO("ComponentContainer: Accessing Component {0} of Entity {1}", typeid(T).name(), entity);
					return componentArray[i];
				}
			}
			//IVY_CORE_WARN("ComponentContainer: Entity {1} does not have a Component of type {0}. Returning default component.", typeid(T).name(), entity);
			return T();
		}

		void onEntityDestroyed(Entity& entity) override
		{
			IVY_CORE_INFO("ComponentContainer: Trigerring onEntityDestroyed: entity={0}", entity);
			removeComponent(entity);
		}
	};
}