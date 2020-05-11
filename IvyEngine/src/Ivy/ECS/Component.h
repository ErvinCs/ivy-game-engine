#pragma once

#include <stdint.h>

#include "Entity.h"

namespace Ivy
{
/*
 *
 */
#define ComponentType uint8_t

	/*
	 *
	 */
	struct Component
	{
	protected:
		ComponentType componentId;	// Unique per Component Type
		Entity entityId;			// Maps to the ID of the owner Entity
	public:
		Component() : componentId(0), entityId(-1) {}
		Component(ComponentType componentId) : componentId(componentId) {}
		Component(ComponentType componentId, Entity entityId) : componentId(componentId), entityId(entityId) {}
		~Component() = default;
		
		inline ComponentType getComponentId() { return componentId; }
		inline Entity getEntityId() { return entityId; }
		inline void setComponentId(ComponentType id) { componentId = id; }
		inline void setEntityId(Entity& entityId) { this->entityId = entityId; }		
	};
}