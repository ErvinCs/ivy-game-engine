#include "ivypch.h"
#include "OpenGLTexture.h"
#include "../../Core/Core.h"
#include "../../Core/Logger.h"

#include <stb_image.h>

namespace Ivy {

	OpenGLTexture::OpenGLTexture(const std::string& path, bool isBaseTexture)
	{
		if (isBaseTexture)
			filepath = Paths::baseTexturePath.string();
		else
			filepath = (Paths::texturesPath / path).string();

		/*int width, height, channels;
		//stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		IVY_CORE_ASSERT(data, "Failed to load image!");
		this->width = width;
		this->height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
		glTextureStorage2D(rendererId, 1, GL_RGB8, width, height);

		glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(rendererId, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);*/
		//rendererId = 0;
		localBuffer = nullptr;
		width = 0;
		height = 0;
		bitsPerPixel = 0;

		// Flip the texture vertically because OpenGL's (0,0) is the bottom left - depends on the texture format
		stbi_set_flip_vertically_on_load(1);
		localBuffer = stbi_load(filepath.c_str(), &width, &height, &bitsPerPixel, 4);

		GLCall(glGenTextures(1, &rendererId));
		GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
		//GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		// Free the copy of the data in the buffer 
		// (TODO: should be stored)
		if (localBuffer)
			stbi_image_free(localBuffer);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		GLCall(glDeleteTextures(1, &rendererId));
	}

	void OpenGLTexture::bind(uint32_t slot) const
	{
		// Specify the texture slot
		// OpenGL allows 32, but it depends on the platform
		//GLCall(glBindTextureUnit(slot, rendererId));
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));

		GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));
	}

}