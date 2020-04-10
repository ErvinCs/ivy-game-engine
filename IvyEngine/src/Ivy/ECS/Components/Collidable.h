#pragma once

#include <glm/glm.hpp>
#include "../Component.h"

namespace Ivy {

	struct Collidable : public Component
	{
	public:
		glm::vec2 centerPosition;
		glm::vec2 halfScale;
		float rotation;

		glm::vec2 unitX;
		glm::vec2 unitY;
		
		Collidable() : Component() {}
		Collidable(glm::vec2 position, float rotation, glm::vec2 scale);	
	};

}