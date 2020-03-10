#pragma once

#include <stdint.h>
#include "glm/vec2.hpp"

namespace Ivy
{
	struct Component
	{
	private:
		uint8_t componentId;	// Unique per Component Type
		//uint16_t entityId;
	public:
		Component(uint8_t componentId) : componentId(componentId) {}
		//Component(uint8_t componentId, uint16_t entityId) : componentId(componentId), entityId(entityId) {}
		
		inline uint8_t getComponentId() { return componentId; }

		//inline uint16_t getEntityId() { return entityId; }
	};

	struct Transform
	{
	public:
		glm::vec2 position;
		float rotation;
		glm::vec2 scale;
	};

	struct Renderable
	{
	public:
		std::string spritePath;
	};
}