#pragma once

#include "System.h"
#include "../../Renderer/Renderer.h"
#include "../../Renderer/Texture.h"
#include "../../Core/ResourcePaths.h"

namespace Ivy {

	/**
	 * System that, when enabled, renders a representation of the collidables held by entities.
	 * Requires a CollidableBox and a Transform.
	 * @see System
	 * @see Renderable
	 * @see CollisionSystem
	 * @see CollidableBox
	 */
	class CollidableGizmoSystem : public System
	{
	private:
		std::shared_ptr<Texture> gizmo = Texture::Create(Paths::collidablePath.string());
	public:
		static bool showGizmos;

		CollidableGizmoSystem() = default;
		CollidableGizmoSystem(EntityContainer& entities)
		{
			this->setEntities(entities);
		}

		/**
		 * Sets the clear color used by the Renderer
		 */
		virtual void init() override;
		/**
		 * Calls the renderer to draw the boxes coresponding to the collidables owned by entities.
		 */
		virtual void update(float deltatime) override;
	};
}

