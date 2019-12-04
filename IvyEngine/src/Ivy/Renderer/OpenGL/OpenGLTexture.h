#pragma once

#include "OpenGLRenderAPI.h"
#include "../Texture.h"

namespace Ivy {

	class OpenGLTexture : public Texture
	{
	private:
		uint32_t rendererId;
		std::string filepath;
		unsigned char* localBuffer;
		int width, height, bitsPerPixel;

	public:
		OpenGLTexture() = default;
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();

		void bind(unsigned int slot = 0) const override;
		void unbind() const override;

		void flipX() const override;
		void flipY() const override;

		inline int getWidth() const override { return width; }
		inline int getHeight() const override { return height; }
	};

}