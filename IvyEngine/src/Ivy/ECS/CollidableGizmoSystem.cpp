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
	{	}

	void CollidableGizmoSystem::update(float deltatime)
	{
		if (showGizmos)
		{
			for (auto& it = entities->begin(); it != entities->end(); it++)
			{
				auto& object = *it;

				auto& collidable = ECS::getInstance().getComponent<CollidableBox>(object);
				if (collidable.getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(CollidableBox).name())->second)
					continue;
				Renderer::DrawRect(collidable.centerPosition, collidable.halfScale * 2.0f + 0.1f, collidable.rotation, gizmo);

			}
		}
	}
}