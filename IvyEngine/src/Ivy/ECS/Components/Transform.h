#pragma once

#include "glm/vec2.hpp"
#include "../Component.h"

namespace Ivy
{
	struct Transform : public Component
	{
	public:
		glm::vec2 position;
		float rotation;
		glm::vec2 scale;
		Transform() : Component() {}

		Transform(glm::vec2 position, float rotation, glm::vec2 scale)
		{
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;
			this->setComponentId(0);
		}

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }
	};
}