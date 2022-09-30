#pragma once

#include <string>
#include "../Component.h"
#include "../../Renderer/Texture.h"

namespace Ivy {
	/**
	 * Encapsulates the Texture used to render an entity
	 * @see Texture
	 */
	struct Renderable : public Component
	{
	public:
		// Path to the texture relative to res/textures
		std::string spritePath;
		// Pointer to the Texture implementation
		std::shared_ptr<Ivy::Texture> texture;

		/**
		 * Base Constructor. Invokes the Base Constructor of `Component`
		 * Sets the Texture to the default texture provided by the engine
		 */
		Renderable() : Component() 
		{
			spritePath = "blank.png";
		}

		/**
		 * Constructs a Renderable by loading the texture at the given path.
		 * @param spritePath The path to the texture
		 */
		Renderable(std::string spritePath);

		/**
		 * Copy Constructor
		 */
		Renderable(const Renderable& other);

		// Used by AS reference counting mechanism
		inline void addReference() { /* do nothing */ }
		// Used by AS reference counting mechanism
		inline void release() { /* do nothing */ }

		Renderable& operator=(const Renderable& other);
	};
}