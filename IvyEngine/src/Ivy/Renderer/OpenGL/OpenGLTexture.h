#pragma once

#include "OpenGLRenderAPI.h"
#include "../Texture.h"
#include "../../Core/ResourcePaths.h"

#include <glad/glad.h>

namespace Ivy {

	/*
	 *
	 */
	class OpenGLTexture : public Texture
	{
	private:
		GLenum rendererId;
		std::string filepath;
		bool isBaseTexture;
		int width, height;
		int bitsPerPixel;
		unsigned char* localBuffer;

	public:
		OpenGLTexture(const std::string& path, bool isBaseTexture);
		~OpenGLTexture();

		virtual void bind(uint32_t slot = 0) const override;

		inline int getWidth() const override { return width; }
		inline int getHeight() const override { return height; }

		virtual void flipX() override;
		virtual void flipY() override;

		virtual bool operator==(const Texture& other) const override
		{
			return rendererId == ((OpenGLTexture&)other).rendererId;
		}
	};

}