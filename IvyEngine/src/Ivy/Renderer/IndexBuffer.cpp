#include "ivypch.h"
#include "IndexBuffer.h"

#include "Renderer.h"
#include "RenderAPI.h"

#include "../Core/Logger.h"
#include "OpenGL/OpenGLIndexBuffer.h"

namespace Ivy {

	IndexBuffer* IndexBuffer::Create(uint32_t* data, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None:    
				IVY_CORE_ERROR("RenderAPI::None is not supported!"); 
				return nullptr;
			case RenderAPI::API::OpenGL:  
				return new OpenGLIndexBuffer(data, size);
		}

		IVY_CORE_ERROR("Unknown RenderAPI!");
		return nullptr;
	}

}