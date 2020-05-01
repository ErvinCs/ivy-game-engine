#pragma once

#include "System.h"
#include "../Entity.h"
#include "../../Renderer/OrthoCamera.h"

namespace Ivy{

	class CameraSystem : public System
	{
	private:
		OrthoCamera* camera;
	public:

		CameraSystem() = default;
		CameraSystem(EntityContainer& entities)
		{
			this->setEntities(entities);
		}
		virtual void init() override;
		virtual void update(float deltatime) override;
	};

}
