#include "ivypch.h"
#include "Texture.h"

#include "Renderer.h"
#include "RenderAPI.h"

#include "../Core/Logger.h"
#include "OpenGL/OpenGLTexture.h"

namespace Ivy {

	std::shared_ptr<Texture> Texture::Create(const std::string& filepath, bool isBaseTexture)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:   
			IVY_CORE_ERROR("RenderAPI::None is not supported!"); 
			return nullptr;
		case RenderAPI::API::OpenGL:  
			return std::make_shared<OpenGLTexture>(filepath, isBaseTexture);
		}

		IVY_CORE_ERROR("Unknown RendererAPI!");
		return nullptr;
	}
}