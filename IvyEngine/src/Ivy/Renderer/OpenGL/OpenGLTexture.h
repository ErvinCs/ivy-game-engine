#pragma once

#include "OpenGLRenderer.h"

namespace Ivy {

	class OpenGLTexture
	{
	private:
		uint32_t rendererId;
		std::string filepath;
		unsigned char* localBuffer;
		int width, height, bitsPerPixel;
	public:
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }
	};

}