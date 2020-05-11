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

	/*
	 *
	 */
	class InspectorLayer : public SortingLayer
	{
	private:
		ComponentType TagID;
		ComponentType RenderableID;
		ComponentType TransformID;
		ComponentType ScriptComponentID;
		ComponentType CollidableBoxID;
	public:
		InspectorLayer();

		~InspectorLayer() = default;

		virtual void imGuiRender() override;
	};
}