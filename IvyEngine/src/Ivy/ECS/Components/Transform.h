#pragma once

#include "glm/vec2.hpp"
#include "../Component.h"

namespace Ivy {
	/**
	 * Represents the transformation of an entity, namely its position, rotation and scale.
	 */
	struct Transform : public Component
	{
	public:
		// Position of the entity
		glm::vec2 position;
		// Rotation of the entity in radians
		float rotation;
		// Scale of the entity
		glm::vec2 scale;

		/**
		 * Base Constructor.
		 * Sets all values to 0.
		 */
		Transform() : Component() 
		{
			position = glm::vec2(0.0f);
			rotation = 0.0f;
			scale = glm::vec2(0.0f);
		}

		/**
		 * Constructs a transform component.
		 * @param position Vec2 representing the position
		 * @param rotation Rotation expressed in radians
		 * @param scale Vec2 representing the scale
		 */
		Transform(glm::vec2 position, float rotation, glm::vec2 scale);

		/**
		 * Copy Constructor
		 */
		Transform(const Transform& other);

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }

		/**
		 * @returns true if this Transform's position is equal to other's position
		 */
		bool operator==(const Transform& other);

		/**
		 * @returns true if this Transform's position is NOT equal to other's position
		 */
		bool operator!=(const Transform& other);

		Transform& operator=(const Transform& other)
	};
}