#pragma once

#include "OpenGLRenderAPI.h"
#include "../Texture.h"
#include "../../Core/ResourcePaths.h"

#include <glad/glad.h>

namespace Ivy {

	/**
	 * Represents a Texture as used by OpenGL.
	 * Stores texture data and provides functionality to bind/unbind it.
	 * @see Texture
	 */
	class OpenGLTexture : public Texture
	{
	private:
		GLenum rendererId;
		std::string filepath;
		// True if this texture should be rendered as the default texture provided by the engine and false otherwise
		bool isBaseTexture;
		// Texture with and height
		int width, height;
		// Size of a pixel
		int bitsPerPixel;
		// Buffer used to store texture data
		unsigned char* localBuffer;

	public:
		/**
		 * Loads the texture data of a PNG, BMP or JPG at `path`.
		 * If `isBaseTexture` is set to true then it renders the base texture provided by the engine.
		 * @param path string representing the path to the texture
		 * @param isBaseTexture true if rendering the base texture and false otherwise
		 */
		OpenGLTexture(const std::string& path, bool isBaseTexture);
		
		
		~OpenGLTexture();

		
		virtual void bind(uint32_t slot = 0) const override;

		// @returns int width of the texture
		inline int getWidth() const override { return width; }
		// @returns int height of the texture
		inline int getHeight() const override { return height; }

		// Flips the texture data on the x-axis
		virtual void flipX() override;
		// Flips the texture data on the y-axis
		virtual void flipY() override;

		/**
		 * @param other Texture
		 * @returns true if this texture is the same as `other` and false otherwise.
		 *  Note that two textures are the same if they have the same renderer id.
		 */
		virtual bool operator==(const Texture& other) const override
		{
			return rendererId == ((OpenGLTexture&)other).rendererId;
		}
	};

}