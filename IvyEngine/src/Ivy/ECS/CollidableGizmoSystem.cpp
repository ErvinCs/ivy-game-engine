#include "ivypch.h"
#include "CollidableGizmoSystem.h"

#include "ECS.h"
#include "Component.h"
#include "Components/Collidable.h"
#include "../Core/ResourcePaths.h"

namespace Ivy
{
	bool CollidableGizmoSystem::showGizmos = false;

	void CollidableGizmoSystem::init() 
	{
		IVY_CORE_INFO("CollidableGizmoSystem: Initializing System");
		RenderCommand::setClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		RenderCommand::clear();
	}

	void CollidableGizmoSystem::update(float deltatime)
	{
		if (showGizmos)
		{
			// If you choose to remove the render system from the ECS then
			//     make sure rendering has begun before entering this method
			for (auto& it = entities->begin(); it != entities->end(); it++)
			{
				auto& object = *it;

				auto& collidable = ECS::getInstance().getComponent<CollidableBox>(object);
				if (collidable.getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(CollidableBox).name())->second)
					continue;
				Renderer::DrawRect(collidable.centerPosition, collidable.halfScale * 2.0f + 0.05f, collidable.rotation, gizmo);
			}
			Renderer::End();
		}
	}
}