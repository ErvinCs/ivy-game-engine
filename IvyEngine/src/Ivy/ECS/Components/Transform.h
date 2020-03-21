#pragma once

#include "glm/vec2.hpp"
#include "../Component.h"

namespace Ivy
{
	struct Transform : public Component
	{
	public:
		glm::vec2 position;
		//float positionX;
		//float positionY;
		float rotation;
		glm::vec2 scale;
		/*float scaleX;
		float scaleY;*/
		Transform() : Component() {}

		//Transform(float positionX, float positionY, float rotation, float scaleX, float scaleY)
		//{
		//	this->positionX = positionX;
		//	this->positionY = positionY;
		//	this->scaleX = scaleX;
		//	this->scaleY = scaleY;
		//	this->rotation = rotation;
		//	this->setComponentId(0); //TODO - Remove hard-coded set id
		//}
		Transform(glm::vec2 position, float rotation, glm::vec2 scale)
		{
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;
			this->setComponentId(0);	//TODO - Remove hard-coded set id
		}

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }

		/*Transform(const Transform& other)
		{
			this->positionX = other.positionX;
			this->positionY = other.positionY;
			this->scaleX = other.scaleX;
			this->scaleY = other.scaleY;
			this->rotation = other.rotation;
			this->setComponentId(0);
		}
		Transform& operator= (const Transform& other)
		{
			this->positionX = other.positionX;
			this->positionY = other.positionY;
			this->scaleX = other.scaleX;
			this->scaleY = other.scaleY;
			this->rotation = other.rotation;
			this->setComponentId(0);
			return *this;
		}*/

	};
}