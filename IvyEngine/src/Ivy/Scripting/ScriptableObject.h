#pragma once

#include <string>

#include <angelscript.h>
#include "../angelscript/add_on/scripthandle/scripthandle.h"

#include "../ECS/Entity.h"
#include "../Core/ResourcePaths.h"

#include "../Core/Logger.h"

namespace Ivy 
{

	/*
	 *
	 */
	class ScriptableObject
	{
	protected:
		std::string name;
		asIScriptObject* scriptObject;
		Entity ownerEntity;
		bool alive;

		int referenceCount;
		asILockableSharedBool* weakReferenceFlag;
	public:
		ScriptableObject();
		ScriptableObject(const std::string& name);
		ScriptableObject(const ScriptableObject& other);
		~ScriptableObject();

		int addReference();
		int release();

		asILockableSharedBool* getWeakRefereneFlag();
		void destoryAndRelease();
		void kill();

		void sendMessage(CScriptHandle message, ScriptableObject* target);
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

		ScriptableObject& operator=(const ScriptableObject& other);
	};

}