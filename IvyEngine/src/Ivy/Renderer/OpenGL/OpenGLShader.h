#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

#include "../Shader.h"

namespace Ivy {

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class OpenGLShader : public Shader
	{
	private:
		std::string filepath;
		uint32_t rendererId;
		// Cache uniforms
		std::unordered_map<std::string, int> uniformLocationCache;

	public:
		// Take in 1 file with both a vertex shader & a fragment shader
		OpenGLShader() = default;
		OpenGLShader(const std::string& filepath);
		~OpenGLShader();

		void bind() const override;
		void unbind() const override;

		// Set uniforms
		virtual void setUniform1f(const std::string& name, float v) override;
		virtual void setUniform1i(const std::string& name, int v) override;
		virtual void setUniform2f(const std::string& name, const glm::vec2& vec2) override;
		virtual void setUniform2i(const std::string& name, const glm::ivec2& vec2) override;
		virtual void setUniform3f(const std::string& name, const glm::vec3& vec3) override;
		virtual void setUniform3i(const std::string& name, const glm::ivec3& vec3) override;
		virtual void setUniform4f(const std::string& name, const glm::vec4& vec4) override;
		virtual void setUniform4i(const std::string& name, const glm::ivec4& vec4) override;
		virtual void setUniformMat4f(const std::string& name, const glm::mat4& matrix) override;

	//private:
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderProgramSource parseShader(const std::string& filepath);
		int getUniformLocation(const std::string& name);

	};

}

