#pragma once

#include "../DesignElement.h"

namespace Ivy
{
	class LevelElement : public DesignElement
	{		
	public:
		static int TagCounter;
		LevelElement(Tag tag, Transform transform);
		LevelElement(Tag tag, Transform transform, Renderable renderable);
		LevelElement(Tag tag, Transform transform, Renderable renderable, CollidableBox collidable);
		LevelElement(Tag tag, Transform transform, Renderable renderable, CollidableBox collidable, ScriptComponent script);

		virtual void dummy() override {}
	};
}