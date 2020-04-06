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
		Transform(glm::vec2 position, float rotation, glm::vec2 scale);
		
		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }
	};
}