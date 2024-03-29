#include "ivypch.h"
#include "OpenGLTexture.h"
#include "../../Core/Core.h"
#include "../../Core/Logger.h"

#include <stb_image.h>

namespace Ivy {

	OpenGLTexture::OpenGLTexture(const std::string& path, bool isBaseTexture)
	{
		if (isBaseTexture)
			filepath = Paths::BASE_TEXTURE_PATH.string();
		else
			filepath = (Paths::TEXTURES_PATH / path).string();

		localBuffer = nullptr;
		width = 0;
		height = 0;
		bitsPerPixel = 0;

		// Flip the texture vertically because OpenGL's (0,0) is the bottom left - depends on the texture format
		stbi_set_flip_vertically_on_load(1);
		localBuffer = stbi_load(filepath.c_str(), &width, &height, &bitsPerPixel, 4);

		GLCall(glGenTextures(1, &rendererId));
		GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));

		// GL_LINEAR - Returns the weighted average of the four texture elements that are closest to the specified texture coordinates
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));	// Texture Minifying function
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));	// Texture Magnifyin function
		// GL_CLAMP_TO_EDGE - Clamp texture coordinates to edges
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));

		if (localBuffer)
			stbi_image_free(localBuffer);
	}

	void OpenGLTexture::flipX()
	{
		//TODO
	}

	void OpenGLTexture::flipY()
	{
		//TODO
	}

	OpenGLTexture::~OpenGLTexture()
	{
		GLCall(glDeleteTextures(1, &rendererId));
	}

	void OpenGLTexture::bind(uint32_t slot) const
	{
		// Specify the texture slot
		// OpenGL allows 32, but it depends on the platform
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));
	}

}