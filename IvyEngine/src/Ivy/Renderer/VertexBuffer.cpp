#include "ivypch.h"
#include "VertexBuffer.h"

#include "Renderer.h"
#include "RenderAPI.h"

#include "../Core/Logger.h"
#include "OpenGL/OpenGLVertexBuffer.h"

namespace Ivy {

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:    
			IVY_CORE_ERROR("RenderAPI::None is not supported!");
			return nullptr;
		case RenderAPI::API::OpenGL:  
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		IVY_CORE_ERROR("Unknown RendererAPI!");
		return nullptr;
	}
}