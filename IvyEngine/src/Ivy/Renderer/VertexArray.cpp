#include "ivypch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "RenderAPI.h"

#include "../Core/Logger.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace Ivy {

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:    
			IVY_CORE_ERROR("RenderAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  
			return std::make_shared<OpenGLVertexArray>();
		}

		IVY_CORE_ERROR("Unknown RenderAPI!");
		return nullptr;
	}
}