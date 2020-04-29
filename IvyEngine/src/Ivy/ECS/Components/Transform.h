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

		Transform() : Component() 
		{
			position = glm::vec2(0.0f);
			rotation = 0.0f;
			scale = glm::vec2(0.0f);
		}
		Transform(glm::vec2 position, float rotation, glm::vec2 scale);
		
		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }

		bool operator==(const Transform& other);
		bool operator!=(const Transform& other);

		Transform& operator=(const Transform& other);

	};
}