#pragma once

#include <glm/glm.hpp>
#include "../Component.h"
#include "../Entity.h"

namespace Ivy 
{
	/**
	 * Represents an Oriented Bounding Box used to determine collision.
	 * @see CollisionSystem
	 */
	struct CollidableBox : public Component
	{
	public:
		// Center of the box
		glm::vec2 centerPosition;
		// Only the half-width & half-height of the scale are needed to compute collision
		glm::vec2 halfScale;
		// Rotation in
		float rotation;
		// If true then collision does not reset the entity to the previous position
		bool isTrigger;
		// Unit vector on the local X axis
		glm::vec2 unitX;
		// Unit vector on the local Y axis
		glm::vec2 unitY;
		
		/**
		 * Base Constructor.
		 * Sets all values to 0.
		 */
		CollidableBox() : Component() 
		{
			centerPosition = glm::vec2(0.0f);
			halfScale = glm::vec2(0.0f);
			rotation = 0.0f;
			isTrigger = false;
			unitX = glm::vec2(0.0f);
			unitY = glm::vec2(0.0f);
		}
		/**
		 * Creates a CollidableBox with the given positoin, rotation and scale.
		 * Computes the unit vectors and caches them.
		 * @param position The position of the box as a vec2
		 * @param rotation The rotation of the box in radians
		 * @param scale The scale of the box as a vec2
		 */
		CollidableBox(glm::vec2 position, float rotation, glm::vec2 scale);

		/**
		 * Copy constructor
		 */
		CollidableBox(const CollidableBox& other);

		// Used by AS reference counting mechanism
		inline void addReference() { /* do nothing */ }
		// Used by AS reference counting mechanism
		inline void release() { /* do nothing */ }

		CollidableBox& operator=(const CollidableBox& other);
	};
}