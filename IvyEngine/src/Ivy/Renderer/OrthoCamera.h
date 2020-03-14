#pragma once

#include <glm/glm.hpp>

namespace Ivy {

	class OrthoCamera
	{
	public:
		OrthoCamera() = default;
		OrthoCamera(const float left, const float right, const float bottom, const float top);
		~OrthoCamera() = default;

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
	
		const glm::mat4& getProjMatrix() const { return projMatrix; }
		const glm::mat4& getViewMatrix() const { return viewMatrix; }
		const glm::mat4& getViewProjMatrix() const { return viewProjMatrix; }
	private:
		void calculateViewMatrix();

	private:
		glm::mat4 projMatrix;
		glm::mat4 viewMatrix;	//Inverse of the transformation matrix of the camera
		glm::mat4 viewProjMatrix;

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;	// Z-Rotation
	};

}
