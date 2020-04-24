#pragma once

#include <glm/glm.hpp>

#include "../ECS/Entity.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/Collidable.h"
#include "../ECS/Components/Renderable.h"
#include "../ECS/Components/Tag.h"
#include "../ECS/Components/ScriptComponent.h"

namespace Ivy {
	enum ElementType
	{
		StandardRoom1 = 0,	//NO ENEMIES
		StandardRoom2,		//NO ENEMIES
		Hallway,			//NO ENEMIES
		ClosedRoom,
		TShaped,
		VerticalWall,
		HorizontalWall,	
		Pillar,	
		Hole, 
		RangedEnemy,	//BOSS
		MeleeEnemy		//BOSS
	};

    class DesignElement
	{
	protected:
		ElementType elementType;
	public:
		Entity entity;
		Tag tag{};
		Transform transform{};

		static int TagCounter;
		const static int ElementTypeCount = 11;
		const static int HostileTypeCount = 8;
	public:
		DesignElement() = default;
		DesignElement(const DesignElement& other);
		DesignElement(const DesignElement&& other);
		DesignElement(Tag tag, Transform transform);

		DesignElement& operator=(const DesignElement& other)
		{
			this->transform = other.transform;
			this->tag = other.tag;
			this->elementType = other.elementType;
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

		inline const ElementType& getElementType()
		{ 
			//IVY_CORE_INFO("Returning Element type : {0}", elementType);
			return this->elementType; 
		}
		inline void setElementType(const ElementType& elementType) 
		{ 
			//IVY_CORE_INFO("Setting Element type to {0}", elementType);
			this->elementType = elementType; 
		}
	};
}