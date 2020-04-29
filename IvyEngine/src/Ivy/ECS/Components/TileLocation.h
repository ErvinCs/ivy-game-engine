#pragma once

#include <stdint.h>
#include <glm/glm.hpp>

#include "../Entity.h"
#include "../Component.h"

namespace Ivy
{
	struct TileLocation : public Component
	{
	public:
		Entity owner;
		float tileIndexX, tileIndexY;
		glm::vec2 previousPosition;

		TileLocation() : Component()
		{
			owner = -1;
			tileIndexX = -1;
			tileIndexY = -1;
			previousPosition = glm::vec2(0.0f);
		}
		TileLocation(float tileIndexX, float tileIndexY, glm::vec2 previousPosition, Entity owner);

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }

		bool operator==(const TileLocation& other);
		bool operator!=(const TileLocation& other);

		TileLocation& operator= (const TileLocation& other);
	};

}