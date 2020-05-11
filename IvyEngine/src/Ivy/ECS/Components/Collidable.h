#pragma once

#include <glm/glm.hpp>
#include "../Component.h"
#include "../Entity.h"

namespace Ivy 
{
	/*
	 *
	 */
	struct CollidableBox : public Component
	{
	public:
		glm::vec2 centerPosition;
		glm::vec2 halfScale;
		float rotation;
		bool isTrigger;

		glm::vec2 unitX;
		glm::vec2 unitY;
		
		CollidableBox() : Component() 
		{
			centerPosition = glm::vec2(0.0f);
			halfScale = glm::vec2(0.0f);
			rotation = 0.0f;
			isTrigger = false;
			unitX = glm::vec2(0.0f);
			unitY = glm::vec2(0.0f);
		}
		CollidableBox(glm::vec2 position, float rotation, glm::vec2 scale);
		CollidableBox(const CollidableBox& other);

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }

		CollidableBox& operator=(const CollidableBox& other);
	};

}