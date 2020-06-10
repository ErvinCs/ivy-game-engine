#pragma once

#include "System.h"

namespace Ivy {
	/**
	 * System used to render the entities by calling the Renderer.
	 * Requires a Renderable and a Transform.
	 * @see System
	 * @see Renderable
	 * @see Renderer
	 */
	class RenderSystem : public System
	{
	public:
		RenderSystem() = default;
		RenderSystem(EntityContainer& entities)
		{
			this->setEntities(entities);
		}
		
		/**
		 * Sets the clear color used by the Renderer
		 */
		virtual void init() override;
		/**
		 * Calls the renderer to draw the texture held in the Renderable component at the position and scale
		 *  determined by the Transform.
		 */
		virtual void update(float deltatime) override;
	};

}
