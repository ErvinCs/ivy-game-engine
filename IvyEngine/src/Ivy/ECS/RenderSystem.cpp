#include "ivypch.h"
#include "RenderSystem.h"

#include "ECS.h"
#include "Components/Renderable.h"
#include "Components/Transform.h"
#include "../Renderer/RenderCommand.h"
#include "../Renderer/Renderer.h"
#include "../Core/Application.h"

namespace Ivy {
	
	void RenderSystem::init()
	{
		IVY_CORE_INFO("RenderSystem: Initializing System");
		RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1 });
		RenderCommand::clear();
	}

	void RenderSystem::update(float deltatime)
	{
		//Ivy::RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1 });
		//Ivy::RenderCommand::clear();
		//Ivy::Renderer::Begin(Application::GetApplication().getCamera());
		for (auto& it = entities->begin(); it != entities->end(); it++)
		{
			auto& object = *it;

			auto& renderable = ECS::getInstance().getComponent<Renderable>(object);
			if (renderable.getComponentId() != uint8_t(1))
				continue;

			auto& transform = ECS::getInstance().getComponent<Transform>(object);
			if (transform.getComponentId() != uint8_t(0))
				continue;
			
			Renderer::DrawRect(transform.position, transform.scale, transform.rotation, renderable.texture);
		}
		//Ivy::Renderer::End();
	}

}