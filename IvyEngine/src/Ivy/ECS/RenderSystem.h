#pragma once

#include "System.h"
#include "../Renderer/OrthoCamera.h"

namespace Ivy {

	class RenderSystem : public System
	{
	public:
		RenderSystem() = default;
		RenderSystem(std::vector<Entity>& entities)
		{
			this->setEntities(entities);
		}
		
		virtual void init() override;
		virtual void update(float deltatime) override;
	};

}
