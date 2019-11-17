#include "ivypch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Ivy {

	OpenGLTexture::OpenGLTexture(const std::string& path)
		: filepath(path)
	{
		rendererId = 0;
		localBuffer = nullptr;
		width = 0;
		height = 0;
		bitsPerPixel = 0;

		// Flip the texture vertically because OpenGL's (0,0) is the bottom left - depends on the texture format
		stbi_set_flip_vertically_on_load(1);
		localBuffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);

		GLCall(glGenTextures(1, &rendererId));
		GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		// Free the copy of the data in the buffer 
		// (TODO: should be stored)
		if (localBuffer)
			stbi_image_free(localBuffer);
	}


	OpenGLTexture::~OpenGLTexture()
	{
		GLCall(glDeleteTextures(1, &rendererId));
	}

	void OpenGLTexture::bind(unsigned int slot) const
	{
		// Specify the texture slot
		// OpenGL allows 32, but it really depends on the platform
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));

		GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));

	}

	void OpenGLTexture::unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

}