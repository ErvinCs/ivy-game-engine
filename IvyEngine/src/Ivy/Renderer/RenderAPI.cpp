#include "ivypch.h"
#include "RenderAPI.h"

#include "Renderer.h"

#include "../Core/Logger.h"
#include "OpenGL/OpenGLRenderAPI.h"

namespace Ivy {

	RenderAPI::API RenderAPI::rAPI = RenderAPI::API::OpenGL;

	std::unique_ptr<RenderAPI> RenderAPI::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			IVY_CORE_ERROR("RenderAPI::None is not supported!");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_unique<OpenGLRenderAPI>();
		}

		IVY_CORE_ERROR("Unknown RenderAPI!");
		return nullptr;
	}

}