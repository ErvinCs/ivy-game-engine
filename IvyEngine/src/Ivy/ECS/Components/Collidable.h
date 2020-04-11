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
		std::unordered_set<Entity> isCollidingWith{};

		glm::vec2 unitX;
		glm::vec2 unitY;
		
		CollidableBox() : Component() {}
		CollidableBox(glm::vec2 position, float rotation, glm::vec2 scale);
	};

}