#pragma once

#include "System.h"
#include "../Entity.h"
#include "../../Renderer/OrthoCamera.h"

namespace Ivy{

	/**
	 * System used for camera manipulation.
	 * Currently only supports binding camera to an entity
	 * @see OrthoCamera
	 */
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
