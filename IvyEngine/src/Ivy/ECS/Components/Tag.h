#pragma once

#include <string>

#include "../Component.h"

namespace Ivy 
{
	/**
	 * Acts as the name of the entity.
	 * Used to display it in the GUI.
	 * Some functions use the Tag to refer to an entity.
	 */
	struct Tag : public Component
	{
	public:
		// The tag used to identify an entity
		std::string tag = "";

		/**
		 * Base constructor.
		 */
		Tag() : Component() {}

		/**
		 * Creates a Tag object with the given tag
		 * @param newTag The tag text
		 */
		Tag(std::string newTag);

		/**
		 * Copy Constructor
		 */
		Tag(const Tag& other);

		// Used by AS reference counting mechanism
		inline void addReference() { /* do nothing */ }
		// Used by AS reference counting mechanism
		inline void release() { /* do nothing */ }

		Tag& operator=(const Tag& other);
	};

}