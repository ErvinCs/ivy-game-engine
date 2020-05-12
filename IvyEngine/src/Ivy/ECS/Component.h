#pragma once

#include <stdint.h>

#include "Entity.h"

namespace Ivy
{
/**
 * The component types are generated on being registerd.
 * Also see: ECS
 */
#define ComponentType uint8_t

	/**
	 * Base class for all components used by the ECS.
	 * Defines the `ComponentType` and the `Entity` owning the component.
	 */
	struct Component
	{
	protected:
		// Unique per Component Type
		ComponentType componentId;	
		// Maps to the ID of the owner Entity
		Entity entityId;			
	public:
		/**
		 * Default constructor. 
		 * Sets its fields to invalid values.
		 * Specifically, sets `componentId` to 0 and entityId to MAX_UINT16
		 */
		Component() : componentId(0), entityId(-1) {}

		/**
		 * Creates a component representing a specific component type 
		 * @param componentId Denotes the type of the component
		 */
		[[DEPRECATED]]
		Component(ComponentType componentId) : componentId(componentId) {}

		/**
		 * Creates a component representing a specific component type and maps it to an entity
		 * @param componentId Denotes the type of the component
		 * @param entityId Marks the owner entity of this component
		 */
		[[DEPRECATED]]
		Component(ComponentType componentId, Entity entityId) : componentId(componentId), entityId(entityId) {}
		~Component() = default;
		
		// @returns The ComponentType
		inline ComponentType getComponentId() { return componentId; }
		// @returns The ID of the entity owning the component
		inline Entity getEntityId() { return entityId; }
		/**
		 * Sets the component ID
		 * @param id ComponentType
		 */
		inline void setComponentId(ComponentType id) { componentId = id; }
		/**
		 * Sets the owner entity
		 * @param entityId Entity
		 */
		inline void setEntityId(Entity& entityId) { this->entityId = entityId; }		
	};
}