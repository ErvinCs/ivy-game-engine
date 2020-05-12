#pragma once

#include <string>
#include <unordered_map>
#include "../../Core/ResourcePaths.h"
#include "glm/glm.hpp"

#include "../Shader.h"

namespace Ivy 
{
	/*
	 *
	 */
	struct ShaderProgramSource
	{
		//
		std::string VertexSource;
		//
		std::string FragmentSource;
	};

	/**
	 *
	 */
	class OpenGLShader : public Shader
	{
	private:
		//
		std::string filepath;
		//
		uint32_t rendererId;
		// Cache uniforms
		std::unordered_map<std::string, int> uniformLocationCache;

	public:
		OpenGLShader() = default;
		// Takes in 1 file with both a vertex shader & a fragment shader
		/**
		 *
		 */
		OpenGLShader(const std::string& filepath);
		/**
		 *
		 */
		~OpenGLShader();

		/**
		 *
		 */
		void bind() const override;

		/**
		 *
		 */
		void unbind() const override;

		// Set 1 float uniform
		virtual void setUniform1f(const std::string& name, float v) override;
		// Set 1 integer uniform
		virtual void setUniform1i(const std::string& name, int v) override;
		// Set float2 uniform
		virtual void setUniform2f(const std::string& name, const glm::vec2& vec2) override;
		// Set int2 uniform
		virtual void setUniform2i(const std::string& name, const glm::ivec2& vec2) override;
		// Set float3 uniform
		virtual void setUniform3f(const std::string& name, const glm::vec3& vec3) override;
		// Set int3 uniform
		virtual void setUniform3i(const std::string& name, const glm::ivec3& vec3) override;
		// Set float4 uniform
		virtual void setUniform4f(const std::string& name, const glm::vec4& vec4) override;
		// Set int4 uniform
		virtual void setUniform4i(const std::string& name, const glm::ivec4& vec4) override;
		// Set float4x4 matrix uniform
		virtual void setUniformMat4f(const std::string& name, const glm::mat4& matrix) override;

		/**
		 *
		 */
		unsigned int compileShader(unsigned int type, const std::string& source);

		/**
		 *
		 */
		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

		/**
		 *
		 */
		ShaderProgramSource parseShader(const std::string& filepath);

		/**
		 *
		 */
		int getUniformLocation(const std::string& name);

	};

}

