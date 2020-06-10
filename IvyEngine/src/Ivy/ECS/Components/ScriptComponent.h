#pragma once

#include <string>

#include "../Component.h"
#include "../../Scripting/ScriptableObject.h"

namespace Ivy
{
	/**
	 * Encapsulates the AS script used to control an entity.
	 * @see ScriptableObject
	 * @see ScriptManager
	 */
	struct ScriptComponent : public Component
	{
	public:
		// Path to the script relative to res/scripts
		std::string scriptName;
		// The object encapsulating the AS script
		ScriptableObject* scriptableObject;

		/**
		 * Base constructor.
		 * Creates a default ScriptableObject and sets the script name to "".
		 */
		ScriptComponent() : Component() 
		{
			this->scriptName = "";
			this->scriptableObject = new ScriptableObject();
		}

		/**
		 * Creates a script with the given name at res/scripts
		 * @param scriptName The name of the script file. Should have the extension ".as".
		 */
		ScriptComponent(std::string scriptName);

		/**
		 * Copy Constructor
		 */
		ScriptComponent(const ScriptComponent& other);

		/**
		 * The Destructor is required to free the `scriptableObject`
		 */
		~ScriptComponent();

		// Used by AS reference counting mechanism
		inline void addReference() { /* do nothing */ }
		// Used by AS reference counting mechanism
		inline void release() { /* do nothing */ }

		ScriptComponent& operator=(const ScriptComponent& other);
	};
}