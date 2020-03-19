#include "ivypch.h"
#include "RenderSystem.h"

#include "ECS.h"
#include "Components/Renderable.h"
#include "Components/Transform.h"
#include "../Renderer/RenderCommand.h"
#include "../Renderer/Renderer.h"

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
			if (renderable.getComponentId() == uint8_t(1))
				continue;

			auto& transform = ECS::getInstance().getComponent<Transform>(object);
			if (transform.getComponentId() == uint8_t(0))
				continue;
			

			Renderer::DrawRect(glm::vec2(transform.positionX, transform.positionY), 
				glm::vec2(transform.scaleX, transform.scaleY), transform.rotation, renderable.texture);
		}
	}

}