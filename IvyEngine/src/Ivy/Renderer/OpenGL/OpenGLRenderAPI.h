#pragma once

#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLIndexBuffer.h"

#include "../RenderAPI.h"

//TODO - Define a BufferElement

namespace Ivy {

	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		OpenGLRenderAPI() = default;
		~OpenGLRenderAPI() = default;
		void init() override;
		void clear() override;
		//void drawIndexed(const OpenGLVertexArray& va, const OpenGLIndexBuffer& ib, const OpenGLShader& shader) override;
		void drawIndexed(const std::shared_ptr<VertexArray>& va) override;
		void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void setClearColor(const glm::vec4& color) override;
	};

}