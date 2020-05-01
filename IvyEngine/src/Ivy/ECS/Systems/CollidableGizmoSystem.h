#pragma once

#include "System.h"
#include "../../Renderer/Renderer.h"
#include "../../Renderer/Texture.h"
#include "../../Core/ResourcePaths.h"

namespace Ivy {
	class CollidableGizmoSystem : public System
	{
	private:
		std::shared_ptr<Texture> gizmo = Texture::Create(Paths::collidablePath.string());
	public:
		static bool showGizmos;

		CollidableGizmoSystem() = default;
		CollidableGizmoSystem(EntityContainer& entities)
		{
			this->setEntities(entities);
		}

		virtual void init() override;
		virtual void update(float deltatime) override;
	};
}

