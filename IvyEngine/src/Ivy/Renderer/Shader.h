#pragma once

#include <glm/glm.hpp>

namespace Ivy 
{
	/**
	 * Base class for representing shader programs implemented per API.
	 * Provides access to uniforms
	 */
	class Shader
	{
	public:
		virtual ~Shader() = default;

		/**
		 * Bind this shader program.
		 */
		virtual void bind() const = 0;

		/**
		 * Unbind this shader program.
		 */
		virtual void unbind() const = 0;

		virtual void setUniform1f(const std::string& name, float v) = 0;
		virtual void setUniform1i(const std::string& name, int v) = 0;
		virtual void setUniform2f(const std::string& name, const glm::vec2& vec2) = 0;
		virtual void setUniform2i(const std::string& name, const glm::ivec2& vec2) = 0;
		virtual void setUniform3f(const std::string& name, const glm::vec3& vec3) = 0;
		virtual void setUniform3i(const std::string& name, const glm::ivec3& vec3) = 0;
		virtual void setUniform4f(const std::string& name, const glm::vec4& vec4) = 0;
		virtual void setUniform4i(const std::string& name, const glm::ivec4& vec4) = 0;
		virtual void setUniformMat4f(const std::string& name, const glm::mat4& matrix) = 0;

		/**
		 * Creates a new Shader instance.
		 * @param filepath path to the shader program.
		 * @returns shared_ptr<Shader> pointing to the created shader.
		 */
		static std::shared_ptr<Shader> Create(const std::string& filepath);
	};

}