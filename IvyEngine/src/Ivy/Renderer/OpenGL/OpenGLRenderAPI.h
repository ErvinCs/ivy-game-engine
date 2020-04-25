#pragma once

#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLIndexBuffer.h"

#include "../RenderAPI.h"



#include <glad/glad.h>
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);



namespace Ivy {

	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		OpenGLRenderAPI() = default;
		~OpenGLRenderAPI() = default;
		void init() override;
		void clear() override;
		void draw(const std::shared_ptr<VertexArray>& va, uint32_t indexCount = 0) override;
		void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void setClearColor(const glm::vec4& color) override;
	};

}