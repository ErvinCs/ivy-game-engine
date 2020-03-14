#include "ivypch.h"
#include "RenderSystem.h"

#include "ECS.h"
#include "Components/Renderable.h"
#include "Components/Transform.h"
#include "../Renderer/RenderCommand.h"
#include "../Renderer/Renderer.h"

#include "../Renderer/Texture.h"

namespace Ivy {
	
	void RenderSystem::init()
	{
		RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1 });
		RenderCommand::clear();
	}

	void RenderSystem::update(float deltatime)
	{
		for (auto& it = entities.begin(); it != entities.end(); it++)
		{
			auto& object = *it;

			auto& renderable = ECS::getInstance().getComponent<Renderable>(object);
			auto& transform = ECS::getInstance().getComponent<Transform>(object);

			Renderer::DrawRect(transform.position, transform.scale, transform.rotation, renderable.texture);
		}
	}

}