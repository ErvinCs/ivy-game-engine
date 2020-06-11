#pragma once

#include <string>
#include <unordered_map>
#include "../../Core/ResourcePaths.h"
#include "glm/glm.hpp"

#include "../Shader.h"

namespace Ivy 
{
	/**
	 * Encapsulates the source code of a vertex shader and a fragment shader
	 */
	struct ShaderProgramSource
	{
		// Vertex shader source code in string format
		std::string VertexSource;
		// Fragment shader source code in string format
		std::string FragmentSource;
	};

	/**
	 * OpenGL Shader program representation.
	 * Provides functionality to set uniforms, bind/unbind shaders and compile shaders.
	 * @see Shader
	 */
	class OpenGLShader : public Shader
	{
	private:
		// Path to the shader file
		std::string filepath;
		uint32_t rendererId;
		// Cached uniforms
		std::unordered_map<std::string, int> uniformLocationCache;

	public:
		OpenGLShader() = default;

		/**
		 * Takes in 1 file with both a vertex shader & a fragment shader.
		 * Parses them, binds them and finally detaches them.
		 * @filepath string of the path to the file containing the 2 shaders
		 */
		OpenGLShader(const std::string& filepath);

		~OpenGLShader();

		/**
		 * Bind this shader program
		 */
		void bind() const override;

		/**
		 * Unbind this shader program
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
		 * Compile a GLSL shader program of the passed type
		 * @param type of the shader program (refer to: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml)
		 * @param source string of the shader program
		 * @returns unsigned int the identifier of the shader program
		 */
		unsigned int compileShader(unsigned int type, const std::string& source);

		/**
		 * Create a GLSL shader program from the given vertex and fragment shader strings.
		 * @param vertexShader string code of the vertex shader
		 * @param fragmentShader string code of the fragment shader
		 * @returns unsigned int the identifier of the shader program
		 */
		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

		/**
		 * Parse the shader code at the given file.
		 * @param filepath string of the path to the shader
		 * @returns ShaderProgramSource struc
		 * @see ShaderProgramSource
		 */
		ShaderProgramSource parseShader(const std::string& filepath);

		/**
		 * Retrieve a value of a uniform from the bound shader
		 * @param name of the uniform
		 * @returns int the location of the uniform
		 */
		int getUniformLocation(const std::string& name);

	};

}

