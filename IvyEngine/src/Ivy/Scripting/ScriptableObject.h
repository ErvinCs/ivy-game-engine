#pragma once

#include <string>

#include <angelscript.h>
#include "../angelscript/add_on/scripthandle/scripthandle.h"

#include "../ECS/Entity.h"
#include "../Core/ResourcePaths.h"

#include "../Core/Logger.h"

namespace Ivy 
{

	/**
	 * An abstraction that represents a physical script.
	 * Maintains the name of the script, a pointer to its script object, its live status and the number of outside references.
	 */
	class ScriptableObject
	{
	protected:
		// Name of the script
		std::string name;
		asIScriptObject* scriptObject;
		// Entity controlled by the script
		Entity ownerEntity;
		// True if the entity is alive, false otherwise
		bool alive;
		// Keeps track of other objects referencing this one
		int referenceCount;
		// Obtains a weak reference flag to another ScriptableObject that signals wether or not it is still alive
		asILockableSharedBool* weakReferenceFlag;
	public:
		/**
		 * Base Constructor. Constructs a live ScriptableObject with no name.
		 */
		ScriptableObject();

		/**
		 * Constructs a SciriptableObject with the given name
		 * @param name string 
		 */
		ScriptableObject(const std::string& name);

		/**
		 * Copy Constructor.
		 * @param other ScriptableObject to be copied
		 */
		ScriptableObject(const ScriptableObject& other);
		~ScriptableObject();

		/**
		 * Increase the reference count of this ScriptableObject
		 * @returns int number of references held by this
		 */
		int addReference();
		/**
		 * Decrease the reference count of this ScriptableObject
		 * @returns int number of references held by this
		 */
		int release();
		
		/**
		 * Release this object.
		 */
		void destoryAndRelease();
		
		/**
		 * Set the alive flag to false.
		 * The object will be released at a later stage
		 */
		void kill();

		/**
		 * Class the `onMessage` function of `target` ScriptableObject, passing it the `message` handle
		 */
		void sendMessage(CScriptHandle message, ScriptableObject* target);
		
		/**
		 * Calls the `onUpdate` function of this ScriptableObject
		 */
		void onUpdate();

		void setOwner(Entity ownerEntity);
		Entity getOwner();	
		inline void setAlive(bool live) { this->alive = live; }
		inline bool isAlive() { return alive; }
		inline const std::string& getName() { return this->name; }
		inline const void setName(const std::string& name) { this->name = (Paths::scriptsPath / name).string(); }
		inline const void setFullPath(const std::string& fullPath) { this->name = fullPath; }
		inline asIScriptObject* getScriptObject() { return this->scriptObject; }
		inline void setScriptObject(asIScriptObject* scriptObject) { this->scriptObject = scriptObject; }
		inline void setWeakRefereneFlag(asILockableSharedBool* weakRefFlag) { this->weakReferenceFlag = weakRefFlag; }
		asILockableSharedBool* getWeakRefereneFlag();

		ScriptableObject& operator=(const ScriptableObject& other);
	};

}