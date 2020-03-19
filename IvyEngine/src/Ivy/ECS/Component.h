#pragma once

#include <stdint.h>


namespace Ivy
{
	struct Component
	{
	protected:
		uint8_t componentId;	// Unique per Component Type
		uint16_t entityId;		// Maps to the ID of the owner Entity
	public:
		Component() : componentId(-1), entityId(-1) {}
		Component(uint8_t componentId) : componentId(componentId) {}
		Component(uint8_t componentId, uint16_t entityId) : componentId(componentId), entityId(entityId) {}
		~Component() = default;
		
		inline uint8_t getComponentId() { return componentId; }

		inline void setComponentId(uint8_t id) { componentId = id; }

		inline uint16_t getEntityId() { return entityId; }

		inline void setEntityId(uint16_t& entityId) { this->entityId = entityId; }

		
	};

	//enum ComponentTypes
	//{

	//};
}