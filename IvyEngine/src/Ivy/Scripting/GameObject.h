#pragma once

#include <string>
//#include <glm/glm.hpp>

#include <angelscript.h>

#include "../angelscript/add_on/scripthandle/scripthandle.h"

namespace Ivy {

	class GameObject
	{
	protected:
		std::string name;
		bool isAlive;
		asIScriptObject* scriptObject;

		int referenceCount;
		asILockableSharedBool* weakReferenceFlag;
	public:
		GameObject();
		~GameObject();

		int addReference();
		int release();
		asILockableSharedBool* getWeakRefereneFlag();
		void destoryAndRelease();
		void sendMessage(CScriptHandle message, GameObject* target);
		void killObject();

		void onUpdate();
	};

}