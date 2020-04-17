#pragma once

#include "DesignElement.h"

namespace Ivy
{

	enum ElementType
	{
		Hallway,
		VerticalWall,
		HorizontalWall,
		Pillar,
		Hole,
		RangedEnemy
	};

	class LevelElement : public DesignElement
	{
	private:
		ElementType elementType;
	public:
		const static int ElementTypeCount = 6;
		const static int HostileTypeCount = 2;
		static int TagCounter;
		LevelElement(Tag tag, Transform transform)
		{
			this->tag = tag;
			this->transform = transform;
		}
		LevelElement(Tag tag, Transform transform, Renderable renderable)
		{
			this->tag = tag;
			this->transform = transform;
			this->renderable = renderable;
		}
		LevelElement(Tag tag, Transform transform, Renderable renderable, CollidableBox collidable)
		{
			this->tag = tag;
			this->transform = transform;
			this->renderable = renderable;
			this->collidable = collidable;
		}
		LevelElement(Tag tag, Transform transform, Renderable renderable, CollidableBox collidable, ScriptComponent script)
		{
			this->tag = tag;
			this->transform = transform;
			this->renderable = renderable;
			this->collidable = collidable;
			this->scriptComponent = script;
		}

		inline const ElementType& getElementType() { return this->elementType; }
		inline void setElementType(const ElementType& elementType) { this->elementType = elementType; }

		virtual void DUMMY_TEMP() override 
		{}
	};
}