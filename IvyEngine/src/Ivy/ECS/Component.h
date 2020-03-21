#pragma once

#include <stdint.h>

#include "Entity.h"

namespace Ivy
{
	struct Component
	{
	protected:
		uint8_t componentId;	// Unique per Component Type
		Entity entityId;		// Maps to the ID of the owner Entity
	public:
		Component() : componentId(-1), entityId(-1) {}
		Component(uint8_t componentId) : componentId(componentId) {}
		Component(uint8_t componentId, Entity entityId) : componentId(componentId), entityId(entityId) {}
		~Component() = default;
		
		inline uint8_t getComponentId() { return componentId; }

		inline Entity getEntityId() { return entityId; }

		inline void setComponentId(uint8_t id) { componentId = id; }

		inline void setEntityId(Entity& entityId) { this->entityId = entityId; }

		
	};

	// TODO - Header of defines for Componenet Type ID (or another way to manage them)
	/*{
		NoneID = -1,
		TransformID = 0,
		RenderableID = 1,
		ScriptComponentID = 2
	};*/
}