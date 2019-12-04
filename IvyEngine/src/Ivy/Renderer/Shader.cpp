#include "ivypch.h"
#include "Shader.h"

#include "Renderer.h"
#include "RenderAPI.h"

#include "../Core/Logger.h"
#include "OpenGL/OpenGLShader.h"

namespace Ivy {

	std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			IVY_CORE_ERROR("RenderAPI::None is not supported!");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}

		IVY_CORE_ERROR("Unknown RendererAPI!");
		return nullptr;
	}

}