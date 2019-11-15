#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

namespace Ivy {

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class OpenGLShader
	{
	private:
		std::string filepath;
		unsigned int rendererId;
		// Cache uniforms
		std::unordered_map<std::string, int> uniformLocationCache;

	public:
		// Take in 1 file with both a vertex shader & a fragment shader
		OpenGLShader(const std::string& filepath);
		~OpenGLShader();

		void bind() const;
		void unbind() const;

		// Set uniforms
		// TODO: templates
		void setUniform1f(const std::string& name, float v);
		void setUniform1i(const std::string& name, int v);
		void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderProgramSource parseShader(const std::string& filepath);
		int getUniformLocation(const std::string& name);

	};

}

