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

		/*

		IVY_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
		glTextureStorage2D(rendererId, 1, texInternalFormat, texWidth, texHeight);

		glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(rendererId, 0, 0, 0, texWidth, texHeight, texDataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);*/

		// Flip the texture vertically because OpenGL's (0,0) is the bottom left - depends on the texture format
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}

		this->texWidth = width;
		this->texHeight = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		this->texInternalFormat = internalFormat;
		this->texDataFormat = dataFormat;

		IVY_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		GLCall(glGenTextures(1, &rendererId));
		GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 1, texInternalFormat, texWidth, texHeight, 0, dataFormat, GL_UNSIGNED_BYTE, data));

		stbi_image_free(data);
	}

	void OpenGLTexture::setData(void* data, uint32_t size)
	{
		uint32_t bpp = texDataFormat == GL_RGBA ? 4 : 3;
		IVY_CORE_ASSERT(size == width * height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(rendererId, 0, 0, 0, texWidth, texHeight, texDataFormat, GL_UNSIGNED_BYTE, data);
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
		GLCall(glBindTextureUnit(slot, rendererId));

		//GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		//GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));
	}

}