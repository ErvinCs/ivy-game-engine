#pragma once

#include <glm/glm.hpp>
#include "../ECS/Entity.h"

namespace Ivy 
{
	/*
	 *
	 */
	class OrthoCamera
	{
	public:
		OrthoCamera() = default;
		OrthoCamera(float left, float right, float bottom, float top);
		~OrthoCamera() = default;

		// Needs testing
		//void zoomCamera(float factor);

		inline const glm::vec3& getPosition() const { return position; }
		inline float getRotation() { return rotation; }
		inline void setPosition(const glm::vec3& position) 
		{ 
			this->position = position; 
			this->calculateViewMatrix(); 
		}
		inline void setRotation(float rotation) 
		{ 
			this->rotation = rotation;
			this->calculateViewMatrix();
		}
	
		inline void setOwner(int entity) { this->owner = entity; }
		inline int getOwner() { return this->owner; }

		inline const glm::mat4& getProjMatrix() const { return projMatrix; }
		inline const glm::mat4& getViewMatrix() const { return viewMatrix; }
		inline const glm::mat4& getViewProjMatrix() const { return viewProjMatrix; }

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;		// Z-Rotation
		int owner = -1;
	private:
		void calculateViewMatrix();

		glm::mat4 projMatrix;
		glm::mat4 viewMatrix;		//Inverse of the transformation matrix of the camera
		glm::mat4 viewProjMatrix;
	};

}
