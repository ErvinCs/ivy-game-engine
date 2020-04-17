#pragma once

#include <glm/glm.hpp>

#include "../ECS/Entity.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/Collidable.h"
#include "../ECS/Components/Renderable.h"
#include "../ECS/Components/Tag.h"
#include "../ECS/Components/ScriptComponent.h"

namespace Ivy {
    class DesignElement
	{
	public:
		Entity entity;
		Tag tag{};
		Transform transform{};
		Renderable renderable{};
		CollidableBox collidable{};
		ScriptComponent scriptComponent{};
	public:
		//TODO: Rework Constructors
		DesignElement()
		{
			this->position = glm::vec2(1.0f, 1.0f);
			this->rotation = 0.0f;
			this->scale = glm::vec2(1.0f, 1.0f);
		}
		DesignElement(glm::vec2 position, float rotation, glm::vec2 scale)
		{
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;
		}
		DesignElement(const DesignElement& other)
		{
			this->position = other.position;
			this->rotation = other.rotation;
			this->scale = other.scale;
		}
		DesignElement(const DesignElement&& other)
		{
			this->position = std::move(other.position);
			this->rotation = std::move(other.rotation);
			this->scale = std::move(other.scale);
		}
	
		virtual void DUMMY_TEMP() = 0;

		DesignElement& operator=(const DesignElement& other)
		{
			this->position = other.position;
			this->rotation = other.rotation;
			this->scale = other.scale;
			return *this;
		}
		bool operator==(const DesignElement& other)
		{ 
			return this->transform == other.transform;
		}
		bool operator!=(const DesignElement& other)
		{
			return !(*this == other);
		}
		bool operator<(const DesignElement& other)
		{
			if (this->transform.position.y < other.transform.position.y) 
				return true;
			if (other.transform.position.y < this->transform.position.y) 
				return false;

			if (this->transform.position.x < other.transform.position.x)
				return true;
			if (other.transform.position.x < this->transform.position.x) 
				return false;

			return false;
		}
		bool operator>(const DesignElement& other)
		{
			if (this->transform.position.y > other.transform.position.y)
				return true;
			if (other.transform.position.y > this->transform.position.y)
				return false;

			if (this->transform.position.x > other.transform.position.x)
				return true;
			if (other.transform.position.x > this->transform.position.x)
				return false;

			return false;
		}
		bool operator<=(const DesignElement& other)
		{
			if (this->transform.position.y <= other.transform.position.y)
				return true;
			if (other.transform.position.y <= this->transform.position.y)
				return false;

			if (this->transform.position.x <= other.transform.position.x)
				return true;
			if (other.transform.position.x <= this->transform.position.x)
				return false;

			return false;
		}
		bool operator>=(const DesignElement& other)
		{
			if (this->transform.position.y >= other.transform.position.y)
				return true;
			if (other.transform.position.y >= this->transform.position.y)
				return false;

			if (this->transform.position.x >= other.transform.position.x)
				return true;
			if (other.transform.position.x >= this->transform.position.x)
				return false;

			return false;
		}
	};
}