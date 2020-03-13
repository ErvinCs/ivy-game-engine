#pragma once

#include "System.h"
#include "../Renderer/OrthoCamera.h"

#include <iostream>
#include <set>

namespace Ivy {

	class RenderSystem : public System
	{
	public:
		RenderSystem() = default;
		RenderSystem(const std::vector<Entity>& entities)
		{
			this->setEntities(entities);
		}
		RenderSystem(const std::vector<Entity>& entities, const OrthoCamera& camera)
		{
			this->setEntities(entities);
			this->camera = camera;
		}
		
		virtual void init() override;
		virtual void update(float deltatime) override;

		void setCamera(const OrthoCamera& camera) { this->camera = camera; }

	private:
		OrthoCamera camera;
	};

}
