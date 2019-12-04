#include "ivypch.h"
#include "OrthoCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Ivy {

	OrthoCamera::OrthoCamera(const float left, const float right, const float bottom, const float top)
		: projMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), viewMatrix(1.0f)
	{
		viewProjMatrix = projMatrix * viewMatrix;
		//leftBorder = left;
		//rightBorder = right;
		//topBorder = top;
		//bottomBorder = bottom;
	}

	void OrthoCamera::calculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));

		viewMatrix = glm::inverse(transform);
		viewProjMatrix = projMatrix * viewMatrix;
	}
}