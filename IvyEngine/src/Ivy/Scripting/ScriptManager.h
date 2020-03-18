#pragma once

#include <angelscript.h>
#include "../angelscript/add_on/scripthandle/scripthandle.h"
#include "../angelscript/add_on/scriptstdstring/scriptstdstring.h"
#include "../angelscript/add_on/scriptbuilder/scriptbuilder.h"
#include "../angelscript/add_on/weakref/weakref.h"

#include "GameObject.h"


namespace Ivy {

	class ScriptManager
	{
	protected:
		struct SController
		{
			SController() : controllerType(0), createFunction(0), onUpdateMethod(0), onMessageMethod(0) {}
			std::string module;
			asITypeInfo* controllerType;
			asIScriptFunction* createFunction;
			asIScriptFunction* onUpdateMethod;
			asIScriptFunction *onMessageMethod;
		};

		bool hasCompileErrors;
		asIScriptEngine* scriptEngine;
		std::vector<asIScriptContext*> contextList;
		std::vector<SController*> controllerList;
	public:
		static ScriptManager& GetInstance()
		{
			static ScriptManager instance{};
			return instance;
		}

		~ScriptManager();

		int init();
		asIScriptObject* createScriptController(const std::string& script, GameObject* gameObject);

		void callOnUpdate(asIScriptObject* scriptObject);
		void callOnMessage(asIScriptObject* scriptObject, CScriptHandle& message, GameObject* caller);

	protected:
		void setMessageCallback(const asSMessageInfo& message);
		asIScriptContext* getScriptContextFromPool(asIScriptFunction* function);
		void returnScriptContextToPool(asIScriptContext* context);
		int callScript(asIScriptContext* context);
		SController* getScriptController(const std::string& script);

		ScriptManager()
		{
			scriptEngine = 0;
			hasCompileErrors = false;
		}
		ScriptManager(const ScriptManager&) = delete;
		ScriptManager& operator=(const ScriptManager&) = delete;
	};

}