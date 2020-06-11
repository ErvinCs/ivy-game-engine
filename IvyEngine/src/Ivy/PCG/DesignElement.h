#pragma once

#include <glm/glm.hpp>

#include "../ECS/Entity.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/Collidable.h"
#include "../ECS/Components/Renderable.h"
#include "../ECS/Components/Tag.h"
#include "../ECS/Components/ScriptComponent.h"

namespace Ivy {

	/**
	 * The type of one DesignElement (Room) in a level
	 * @see DesignElement
	 */
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
		RangedEnemy,	
		MeleeEnemy		
	};

	/**
	 * Represents one element of a level.
	 * The element is treated as a tagged entity and neccesarily has a Transform.
	 * @see Entity
	 * @see Tag
	 * @see Transform
	 */
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


		/**
		 * Copies the transform, tag, and element type of another DesignElement
		 * @returns DesignElement&
		 */
		DesignElement& operator=(const DesignElement& other)
		{
			this->transform = other.transform;
			this->tag = other.tag;
			this->elementType = other.elementType;
			return *this;
		}

		/**
		 * @returns true if the transform of this is equal to the transform of other and false otherwise
		 * @see Transform
		 */
		bool operator==(const DesignElement& other)
		{ 
			return this->transform == other.transform;
		}

		/**
		 * @returns false if the transform of this is equal to the transform of other and true otherwise
		 * @see Transform
		 */
		bool operator!=(const DesignElement& other)
		{
			return !(*this == other);
		}

		/**
		 * @param other DesignElement
		 * @returns true if this has its transform position smaller than other.
		 *  First the Y-Axis position is compared; if equal then the X-Axis position is compared.
		 *  If equal in all respects returns false.
		 */
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

		/**
		 * @param other DesignElement
		 * @returns true if this has its transform position greater than other.
		 *  First the Y-Axis position is compared; if equal then the X-Axis position is compared.
		 *  If equal in all respects returns false.
		 */
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

		/**
		 * @param other DesignElement
		 * @returns true if this has its transform position smaller or equal than other.
		 *  First the Y-Axis position is compared; if equal then the X-Axis position is compared.
		 *  If equal in all respects returns false.
		 */
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

		/**
		 * @param other DesignElement
		 * @returns true if this has its transform position greater or equal than other. 
		 *  First the Y-Axis position is compared; if equal then the X-Axis position is compared.
		 *  If equal in all respects returns false.
		 */
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

		/**
		 * @returns ElementType& of this DesignElement
		 */
		inline const ElementType& getElementType()
		{ 
			return this->elementType; 
		}

		/**
		 * Sets the element type of this DesignElement
		 * @param elementType the type of room
		 */
		inline void setElementType(const ElementType& elementType) 
		{ 
			this->elementType = elementType; 
		}
	};
}