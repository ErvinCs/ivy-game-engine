#include "ivypch.h"
#include "Context.h"

#include "Renderer.h"
#include "RenderAPI.h"

#include "../Core/Logger.h"
#include "OpenGL/OpenGLContext.h"

namespace Ivy {
	
	std::unique_ptr<Context> Context::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			IVY_CORE_ERROR("RenderAPI::None is not supported!");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		IVY_CORE_ERROR("Unknown RenderAPI!");
		return nullptr;
	}
}