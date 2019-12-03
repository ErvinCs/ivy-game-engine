#include "ivypch.h"
#include "OpenGLShader.h"
#include "OpenGLRenderAPI.h"

#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>

namespace Ivy {

	OpenGLShader::OpenGLShader(const std::string& filepath) : filepath(filepath), rendererId(0)
	{
		ShaderProgramSource source = parseShader(filepath);
		rendererId = createShader(source.VertexSource, source.FragmentSource);
	}

	OpenGLShader::~OpenGLShader()
	{
		GLCall(glDeleteProgram(rendererId));
	}

	void OpenGLShader::bind() const
	{
		GLCall(glUseProgram(rendererId));
	}

	void OpenGLShader::unbind() const
	{
		GLCall(glUseProgram(0));
	}

	void OpenGLShader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
	}

	void OpenGLShader::setUniform1f(const std::string& name, float v)
	{
		GLCall(glUniform1f(getUniformLocation(name), v));
	}

	void OpenGLShader::setUniform1i(const std::string& name, int v)
	{
		GLCall(glUniform1i(getUniformLocation(name), v));
	}

	void OpenGLShader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		// GLboolean transpose - OpenGL uses matrices sorted by columns (and so does glm) - set to true otherwise
		GLint location = glGetUniformLocation(rendererId, name.c_str());
		GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)););  //&matrix[0][0]
	}


	int OpenGLShader::getUniformLocation(const std::string& name)
	{
		// Don't search for the location if it is already in cache
		if (uniformLocationCache.find(name) != uniformLocationCache.end())
			return uniformLocationCache[name];

		// A shader must already be bound before using Uniforms
		// Retrieve the location of the uniform
		// Check if the uniform can be found; Will return -1 if the uniform is not used (it will be stripped at compile-time)
		GLCall(int uniformLocation = glGetUniformLocation(rendererId, name.c_str()));
		if (uniformLocation == -1)
		{
			std::cout << "[Warn] Uniform '" << name << "' does not exist!" << std::endl;
		}
		// Cache the uniform location
		uniformLocationCache[name] = uniformLocation;

		return uniformLocation;
	}

	unsigned int OpenGLShader::compileShader(unsigned int type, const std::string& source)
	{
		GLCall(unsigned int id = glCreateShader(type));
		const char* src = source.c_str();
		GLCall(glShaderSource(id, 1, &src, nullptr));
		GLCall(glCompileShader(id));

		// Error handling
		int result;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			// The shader did not compile successfully 
			int length;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLCall(glGetShaderInfoLog(id, length, &length, message));

			std::cout << "Failed to compile "
				<< (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
				<< " shader!" << std::endl;
			std::cout << message << std::endl;

			GLCall(glDeleteShader(id));

			return 0;
		}

		return id;
	}

	// The std::string below are the actual source code of the shader. 
	// Will be compiled, link the 2 shaders together into 1 single shader & give back a UID for the generated shader.
	unsigned int OpenGLShader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		// OpenGL provides it's own wrappers for data types (but it still understands raw C data types)
		GLCall(unsigned int program = glCreateProgram());

		// Create 2 shader objects
		unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

		// Link the 2 shaders
		GLCall(glAttachShader(program, vs));
		GLCall(glAttachShader(program, fs));
		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		// Shaders already linked into a program, so we can free memory
		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));

		return program;

	}

	// Parse the file Basic.shader & divide its code
	ShaderProgramSource OpenGLShader::parseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1
		};

		ShaderType type = ShaderType::NONE;
		std::stringstream ss[2];
		std::string line;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					// Vertex mode - add to vertex shader string
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					// Fragment mode - add to fragment shader string
					type = ShaderType::FRAGMENT;
				}
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

}