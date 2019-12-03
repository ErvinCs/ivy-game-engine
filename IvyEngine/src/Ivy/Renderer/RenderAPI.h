#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "VertexArray.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

namespace Ivy {

	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0, 
			OpenGL = 1
		};
	public:
		virtual void init() = 0;
		virtual void clear() = 0;
		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		//virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;//
		virtual void drawIndexed(const OpenGLVertexArray& va, const OpenGLIndexBuffer& ib, const OpenGLShader& shader) = 0;
		/////////////////////// TEMP /////////////////////////////////////////////////////
		inline static API getAPI() { return rAPI; }
	private:
		static API rAPI;
	};

}