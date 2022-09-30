#include "ivypch.h"
#include "CameraSystem.h"

#include "../ECS.h"
#include "../../Core/Logger.h"
#include "../../Core/Application.h"

namespace Ivy {
	void CameraSystem::init()
	{
		IVY_CORE_INFO("CameraSystem: Initializing System");
		camera = &Application::GetCamera();
		if (camera == nullptr)
		{
			IVY_CORE_ERROR("CameraSystem::Camera is null!");
		}
	}

	void CameraSystem::update(float deltatime)
	{
		if (camera->getOwner() != -1) {
			Entity owner = camera->getOwner();
			camera->setPosition(glm::vec3(ECS::getInstance().getComponent<Transform>(owner).position, 0.0f));
		}
	}
}