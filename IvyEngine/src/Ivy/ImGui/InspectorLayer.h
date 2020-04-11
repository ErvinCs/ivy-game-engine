#pragma once

#include "../Core/SortingLayer.h"

#include "../ECS/ECS.h"
#include "../ECS/Entity.h"
#include "../ECS/Component.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/Renderable.h"
#include "../ECS/Components/ScriptComponent.h"
#include "../ECS/Components/Tag.h"
#include "../ECS/Components/Collidable.h"

namespace Ivy {
	class InspectorLayer : public SortingLayer
	{
	private:
		ComponentType TagID;
		ComponentType RenderableID;
		ComponentType TransformID;
		ComponentType ScriptComponentID;
		ComponentType CollidableBoxID;
	public:
		InspectorLayer()
		{
			TransformID = ECS::getInstance().getComponentTypes().find(typeid(Transform).name())->second;
			RenderableID = ECS::getInstance().getComponentTypes().find(typeid(Renderable).name())->second;
			ScriptComponentID = ECS::getInstance().getComponentTypes().find(typeid(ScriptComponent).name())->second;
			TagID = ECS::getInstance().getComponentTypes().find(typeid(Tag).name())->second;
			CollidableBoxID = ECS::getInstance().getComponentTypes().find(typeid(CollidableBox).name())->second;

		}
		~InspectorLayer() = default;

		virtual void imGuiRender() override;
	};
}