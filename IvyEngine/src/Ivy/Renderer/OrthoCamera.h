#pragma once

#include <glm/glm.hpp>
#include "../ECS/Entity.h"

namespace Ivy 
{
	/**
	 * Represents an orthographic camera used to capture the scene
	 */
	class OrthoCamera
	{
	public:

		OrthoCamera() = default;

		/**
		 * Creates an orthographic camera with the given margins.
		 * @param left distance from the center to the left edge
		 * @param right distance from the center to the right edge
		 * @param top distance from the center to the top edge
		 * @param bottom distance from the center to the bottom edge
		 */
		OrthoCamera(float left, float right, float bottom, float top);
		~OrthoCamera() = default;

		/**
		 * @returns vec3 position of the camera
		 */
		inline const glm::vec3& getPosition() const { return position; }

		/**
		 * @returns float rotation of the camera
		 */
		inline float getRotation() { return rotation; }

		/**
		 * Move the camera to the given position and recalculate its view matrix
		 * @param position vec3 representing the new postion of the camera
		 */
		inline void setPosition(const glm::vec3& position) 
		{ 
			this->position = position; 
			this->calculateViewMatrix(); 
		}

		/**
		 * Rotate the camera and recalculate its view matrix
		 * @param rotation by which to rotate the camera in radians
		 */
		inline void setRotation(float rotation) 
		{ 
			this->rotation = rotation;
			this->calculateViewMatrix();
		}
	
		/**
		 * Set the owner Entity of the camera. The camera will follow the owner entity such that it is
		 *  at the screen center at all times
		 * @param entity int equal to th owner Entity
		 * @see Entity
		 */
		inline void setOwner(int entity) { this->owner = entity; }

		/**
		 * @returns int equal to the owner Entity of the camera
		 * @see Entity
		 */
		inline int getOwner() { return this->owner; }

		/**
		 * @returns mat4 the projection matrix
		 */
		inline const glm::mat4& getProjMatrix() const { return projMatrix; }

		/**
		 * @returns mat4 the view matrix
		 */
		inline const glm::mat4& getViewMatrix() const { return viewMatrix; }

		/**
		 * @returns mat4 the product: (viewMatrix * projectionMatrix)
		 */
		inline const glm::mat4& getViewProjMatrix() const { return viewProjMatrix; }

		// Position of the camera
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		// Rotation of the camera on the Z-Axis
		float rotation = 0.0f;		
		// The owner Entity. The camera will follow this Entity if it is different from -1.
		int owner = -1;
	private:
		/**
		 * Calculates the camera view matrix by taking into accoutn its position and rotation.
		 * Multiplies its obtained view matrix with the projection matrix and caches the result in viewProjMatrix.
		 */
		void calculateViewMatrix();

		// Linear projection matrix
		glm::mat4 projMatrix;
		// Inverse of the camera projection matrix
		glm::mat4 viewMatrix;		
		// Caches the product: ViewMatrix * ProjectionMatrix
		glm::mat4 viewProjMatrix;
	};

}
