#pragma once

#include "System.h"
#include "../Entity.h"
#include "../../Renderer/OrthoCamera.h"

namespace Ivy {
	/**
	 * System used for camera manipulation.
	 * Currently only supports binding camera to an entity
	 * @see OrthoCamera
	 */
	class CameraSystem : public System
	{
	private:
		// Points to the global OrthoCamera
		OrthoCamera* camera = nullptr;
	public:

		CameraSystem() = default;

		CameraSystem(EntityContainer& entities)
		{
			this->setEntities(entities);
		}

		// Gets the pointer to the global OrthoCamera
		virtual void init() override;

		/**
		 * If the camera has no owner entity then no update is performed.
		 * Otherwise the camera updates the view matrix such that the followed entity is in the center.
		 */
		virtual void update(float deltatime) override;
	};
}