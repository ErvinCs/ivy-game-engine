#include "ivypch.h"

#include "LevelElement.h"

namespace Ivy
{
	int LevelElement::TagCounter = 0;

	LevelElement::LevelElement(Tag tag, Transform transform)
	{
		this->tag = tag;
		this->transform = transform;
	}
	LevelElement::LevelElement(Tag tag, Transform transform, Renderable renderable)
	{
		this->tag = tag;
		this->transform = transform;
		this->renderable = renderable;
	}
	LevelElement::LevelElement(Tag tag, Transform transform, Renderable renderable, CollidableBox collidable)
	{
		this->tag = tag;
		this->transform = transform;
		this->renderable = renderable;
		this->collidable = collidable;
	}
	LevelElement::LevelElement(Tag tag, Transform transform, Renderable renderable, CollidableBox collidable, ScriptComponent script)
	{
		this->tag = tag;
		this->transform = transform;
		this->renderable = renderable;
		this->collidable = collidable;
		this->scriptComponent = script;
	}
}