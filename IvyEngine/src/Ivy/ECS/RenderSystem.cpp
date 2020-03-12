#include "ivypch.h"
#include "RenderSystem.h"

#include "ECS.h"
#include "Components/Renderable.h"
#include "Components/Transform.h"
#include "../Renderer/RenderCommand.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Texture.h"
#include "../Renderer/OpenGL/OpenGLTexture.h"

namespace Ivy {
	
	void RenderSystem::init()
	{
		RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	}

	void RenderSystem::update(float deltatime)
	{
		//std::shared_ptr<std::set<Entity>> entts = getEntities();
		std::set<Entity> entts = getEntities();

		RenderCommand::clear();
		Renderer::Begin(*camera);
	

		for (auto& it = entts.begin(); it != entts.end(); it++)
		{
			auto object = *it;

			auto& renderable = ECS::getInstance().getComponent<Renderable>(object);
			auto& transform = ECS::getInstance().getComponent<Transform>(object);
			std::shared_ptr<Ivy::Texture> texture = Texture::Create(renderable.spritePath);

			Renderer::DrawRect(transform.position, transform.scale, transform.rotation, texture);
		}

		Renderer::End();
	}

}