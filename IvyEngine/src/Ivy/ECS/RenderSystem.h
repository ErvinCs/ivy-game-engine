#pragma once

#include "System.h"
#include "../Renderer/OrthoCamera.h"

#include <iostream>
#include <set>

namespace Ivy {

	class RenderSystem : public System
	{
	public:
		RenderSystem(const std::set<Entity>& entities)//(const std::shared_ptr<std::set<Entity>>& entities)
		{
			this->setEntities(entities);
		}
		
		virtual void init() override;
		virtual void update(float deltatime) override;

		void setCamera(std::shared_ptr<OrthoCamera>& camera) { this->camera = camera; }

	private:
		std::shared_ptr<OrthoCamera> camera;
	};

}
