#pragma once

#include "OpenGLRenderAPI.h"
#include "../Texture.h"

#include <glad/glad.h>

namespace Ivy {

	class OpenGLTexture : public Texture
	{
	private:
		GLenum rendererId;
		std::string filepath;
		int width, height;
		int bitsPerPixel;
		unsigned char* localBuffer;

	public:
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();

		virtual void bind(uint32_t slot = 0) const override;

		inline int getWidth() const override { return width; }
		inline int getHeight() const override { return height; }
	};

}