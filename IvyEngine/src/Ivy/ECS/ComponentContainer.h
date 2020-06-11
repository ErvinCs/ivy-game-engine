#pragma once

#include <array>
#include "Entity.h"
#include "../Exceptions/ComponentNotFoundException.h"
#include "../Core/Logger.h"

namespace Ivy {
	/**
	 * The base class for the templated component containers aggregated in `ECS`.
	 * Defines `onEntityDestroyed(Entity&)` and `clearCoponents` as pure virtual methods, called by the `ECS`
	 * @see ECS
	 */
	class BaseComponentContainer
	{
	public:
		virtual ~BaseComponentContainer() = default;
		virtual void onEntityDestroyed(Entity& entity) = 0;
		virtual void clearComponents() = 0;
	};

	/**
	 * Encapsulates a pre-allocated array of a component type.
	 */
	template<typename T>
	class ComponentContainer : public BaseComponentContainer
	{
	private:
		// Array of components
		std::array<T, MAX_Entities> componentArray{};
		// The number of owned components in the array
		int size;
	public:
		/**
		 * Base constructor. Sets size to 0.
		 */
		ComponentContainer()
		{
			this->size = 0;
		}
		
		/**
		 * Provides access to the underlying array.
		 */
		std::array<T, MAX_Entities>& getComponentArray()
		{
			return this->componentArray;
		}

		/**
		 * @return int The number of owned components
		 */
		int& getSize()
		{
			return this->size;
		}

		/**
		 * Adds a component to the passed entity.
		 * Note that it only increases the array size and replaces the component at that index with the new component
		 * @param entity The entity that should own the component
		 * @param component The component to be added
		 */
		void addComponent(Entity& entity, T component) 
		{
			IVY_CORE_INFO("ComponentContainer: Adding Component {0} to Entity {1}", typeid(T).name(), entity);
			component.setEntityId(entity);
			componentArray[size] = component;
			size++;

		}

		/**
		 * Removes the component owned by entity
		 * @param entity The entity owning the component to be removed
		 */
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
					break;
				}
			}
		}

		/**
		 * Get the component owned by entity
		 * @returns the component of entity
		 */
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

		/**
		 * This method is called when destroying an entity.
		 * Removes all components of the destroyed entity
		 * @param entity The entity that was destroyed
		 */
		void onEntityDestroyed(Entity& entity) override
		{
			removeComponent(entity);
		}

		/**
		 * Sets the number of components to 0.
		 */
		void clearComponents() override
		{
			this->size = 0;
		}
	};
}