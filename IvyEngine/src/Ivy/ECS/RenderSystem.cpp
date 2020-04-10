#include "ivypch.h"
#include "RenderSystem.h"

#include "ECS.h"
#include "Component.h"
#include "Components/Renderable.h"
#include "Components/Transform.h"
#include "../Renderer/RenderCommand.h"
#include "../Renderer/Renderer.h"
#include "../Core/Application.h"
//#include "../ECS/ComponentRegistration.h"

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
			if (renderable.getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(Renderable).name())->second)
				continue;

			auto& transform = ECS::getInstance().getComponent<Transform>(object);
			if (transform.getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(Transform).name())->second)
				continue;
			
			Renderer::DrawRect(transform.position, transform.scale, transform.rotation, renderable.texture);
		}
		//Ivy::Renderer::End();
	}

}