#pragma once

#include <glm/glm.hpp>
#include "../Component.h"
#include "../Entity.h"
#include <unordered_set>

namespace Ivy {

	struct CollidableBox : public Component
	{
	public:
		glm::vec2 centerPosition;
		glm::vec2 halfScale;
		float rotation;
		bool isTrigger;
		std::unordered_set<Entity> isCollidingWith;

		glm::vec2 unitX;
		glm::vec2 unitY;
		
		CollidableBox() : Component() 
		{
			glm::vec2 centerPosition = glm::vec2(0.0f);
			glm::vec2 halfScale = glm::vec2(0.0f);
			float rotation = 0.0f;
			bool isTrigger = false;
			glm::vec2 unitX = glm::vec2(0.0f);
			glm::vec2 unitY = glm::vec2(0.0f);
			isCollidingWith = this->isCollidingWith = std::unordered_set<Entity>();
		}
		CollidableBox(glm::vec2 position, float rotation, glm::vec2 scale);

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }

		//CollidableBox& operator=(const CollidableBox& other);
	};

}