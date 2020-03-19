#pragma once

#include <string>

#include <angelscript.h>
#include "../angelscript/add_on/scripthandle/scripthandle.h"

#include "../ECS/Entity.h"

namespace Ivy {

	class ScriptableObject
	{
	protected:
		std::string name;
		bool isAlive;
		asIScriptObject* scriptObject;
		Entity ownerEntity;

		int referenceCount;
		asILockableSharedBool* weakReferenceFlag;
	public:
		//ScriptableObject();
		ScriptableObject(const std::string& name);
		~ScriptableObject();

		int addReference();
		int release();
		asILockableSharedBool* getWeakRefereneFlag();
		void destoryAndRelease();
		void sendMessage(CScriptHandle message, ScriptableObject* target);
		void killObject();

		void onUpdate();

		void setOwner(Entity ownerEntity);
		Entity getOwner();

		inline const std::string& getName() { return this->name; }
		inline const bool& getIsAlive() { return isAlive; }
		inline asIScriptObject* getScriptObject() { return this->scriptObject; }
		inline void setScriptObject(asIScriptObject* scriptObject) { this->scriptObject = scriptObject; }
	};

}