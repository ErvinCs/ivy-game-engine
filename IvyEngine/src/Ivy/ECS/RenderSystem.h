#pragma once

#include "System.h"

namespace Ivy {

	class RenderSystem : public System
	{
	public:
		RenderSystem() = default;
		RenderSystem(const std::vector<Entity>& entities)
		{
			this->setEntities(entities);
		}
		
		virtual void init() override;
		virtual void update(float deltatime) override;
	};

}
