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
	/**
	 * Creates a new layer containing the ImGUI for manipulation the game objects properties.
	 * I.e. the properties of the Components mapped to Entities.
	 * @see SortingLayer
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
		/**
		 * Initalize the `ComponentType`s identifiers.
		 */
		InspectorLayer();
		~InspectorLayer() = default;

		/**
		 * Renders the ImGUI for the `InspectorLayer`.
		 * Called every frame.
		 */
		virtual void imGuiRender() override;
	};
}