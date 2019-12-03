#include "ivypch.h"
#include "RenderAPI.h"



void GLClearError()
{
	// Get the errors until all the flags are cleared
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	// While errors are actually retrieved
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error]: " << error
			<< "; function: " << function
			<< "; file: " << file
			<< "; line: " << line
			<< std::endl;
		return false;
	}
	return true;
}

namespace Ivy {

	RenderAPI::API RenderAPI::rAPI = RenderAPI::API::OpenGL;

}