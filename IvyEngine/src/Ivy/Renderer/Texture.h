#pragma once

#include <string>

namespace Ivy 
{
	/**
	 * Base class for Textures implemented per API.
	 * Provides access to texture data
	 */
	class Texture
	{
	public:
		virtual ~Texture() = default;

		/**
		 * Bind a texture to one of the available texture slots.
		 * Note that the number of slots depends on the machine.
		 * @param slot texture slot identifier
		 */
		virtual void bind(uint32_t slot = 0) const = 0;

		// @returns int width of the texture
		virtual int getWidth() const = 0;
		// @returns int height of the texture
		virtual int getHeight() const = 0;

		// Flips the texture on the x-axis
		virtual void flipX() = 0;

		// Flips the texture on the y-axis
		virtual void flipY() = 0;

		// Compare two textures
		virtual bool operator==(const Texture& other) const = 0;

		/**
		 * Creates a new concrete texture depending on the used render API.
		 * @param filepath string to the texture 
		 * @param isBaseTexture true if rendering the base texture provided by the engine, false otherwise
		 * @returns shared_ptr<Texture> pointing to the actual texture
		 */
		static std::shared_ptr<Texture> Create(const std::string& filepath, bool isBaseTexture = false);
	};

}