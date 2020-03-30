#include "ivypch.h"
#include "ScriptManager.h"

#include "MethodWrappers.h"

#include "../Core/Timestep.h"
#include "../Core/Logger.h"
#include "../Core/InputHandler.h"
#include <new>

#include <glm/glm.hpp>

// TEMPORARY - THIS IS HERE ONLY FOR: Timestep globalTime
#include "../Core/Application.h"

namespace Ivy {



	ScriptManager::~ScriptManager()
	{
		for (unsigned int n = 0; n < controllerList.size(); n++)
			delete controllerList[n];

		for (unsigned int n = 0; n < contextList.size(); n++)
			contextList[n]->Release();

		if (scriptEngine)
			scriptEngine->ShutDownAndRelease();
	}

	int ScriptManager::init()
	{
		int r;

		scriptEngine = asCreateScriptEngine();

		// Set the message callback to print the human readable messages that the engine gives in case of errors
		r = scriptEngine->SetMessageCallback(asMETHOD(ScriptManager, setMessageCallback), this, asCALL_THISCALL); assert(r >= 0);

		// Register the string type
		RegisterStdString(scriptEngine);

		// Register the generic handle type, called 'ref' in the script
		RegisterScriptHandle(scriptEngine);

		// Register the weak ref template type
		RegisterScriptWeakRef(scriptEngine);

		// Register Timestep
		/*r = scriptEngine->RegisterObjectType("Timestep", 0, asOBJ_REF); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Timestep", asBEHAVE_ADDREF, "void f()", asMETHOD(Timestep, addReference), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Timestep", asBEHAVE_RELEASE, "void f()", asMETHOD(Timestep, release), asCALL_THISCALL); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Timestep", "Timestep &opAddAssign(const Timestep& in)",
			asMETHODPR(Timestep, operator+=, (const Timestep&), Timestep&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timestep &opSubAssign(const Timestep& in)",
			asMETHODPR(Timestep, operator-=, (const Timestep&), Timestep&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timestep &opMulAssign(const Timestep& in)",
			asMETHODPR(Timestep, operator*=, (const Timestep&), Timestep&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timestep &opDivAssign(const Timestep& in)",
			asMETHODPR(Timestep, operator/=, (const Timestep&), Timestep&), asCALL_THISCALL); assert(r >= 0);
		
		r = scriptEngine->RegisterObjectMethod("Timestep", "float &opAddAssign(const float& in)",
			asMETHODPR(Timestep, operator+=, (const float&), float&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float &opSubAssign(const float& in)",
			asMETHODPR(Timestep, operator-=, (const float&), float&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float &opMulAssign(const float& in)",
			asMETHODPR(Timestep, operator*=, (const float&), float&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float &opDivAssign(const float& in)",
			asMETHODPR(Timestep, operator/=, (const float&), float&), asCALL_THISCALL); assert(r >= 0);*/

		/*r = scriptEngine->RegisterObjectMethod("Timestep", "Timesteop opAdd(const Timestep &in)",
			asFUNCTIONPR(operator+, (const Timestep&, const Timestep&), Timestep), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timesteop opSub(const Timestep &in)",
			asFUNCTIONPR(operator-, (const Timestep&, const Timestep&), Timestep), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timesteop opMul(const Timestep &in)",
			asFUNCTIONPR(operator*, (const Timestep&, const Timestep&), Timestep), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timesteop opDiv(const Timestep &in)",
			asFUNCTIONPR(operator/, (const Timestep&, const Timestep&), Timestep), asCALL_CDECL_OBJFIRST); assert(r >= 0);
			
		r = scriptEngine->RegisterObjectMethod("Timestep", "float opAdd(const float &in)",
			asFUNCTIONPR(operator+, (const Timestep&, const float&), float), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float opSub(const float &in)",
			asFUNCTIONPR(operator-, (const Timestep&, const float&), float), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float opMul(const float &in)",
			asFUNCTIONPR(operator*, (const Timestep&, const float&), float), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float opDiv(const float &in)",
			asFUNCTIONPR(operator/, (const Timestep&, const float&), float), asCALL_CDECL_OBJFIRST); assert(r >= 0);
			*/

		// Register global time variable
		r = scriptEngine->RegisterGlobalProperty("float deltatime", &Application::getInstance().globalTime); assert(r >= 0);
		

		// Register ScriptableObject. The scripts cannot create these directly, so there is no factory function.
		r = scriptEngine->RegisterObjectType("ScriptableObject", 0, asOBJ_REF); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("ScriptableObject", asBEHAVE_ADDREF, "void f()", asMETHOD(ScriptableObject, addReference), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("ScriptableObject", asBEHAVE_RELEASE, "void f()", asMETHOD(ScriptableObject, release), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("ScriptableObject", asBEHAVE_GET_WEAKREF_FLAG, "int &f()", asMETHOD(ScriptableObject, getWeakRefereneFlag), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("ScriptableObject", "void setOwner(uint16 ownerEntity)", asMETHOD(ScriptableObject, setOwner), asCALL_THISCALL); assert(r >= 0);

		// The script can kill the owning object
		//r = scriptEngine->RegisterObjectMethod("ScriptableObject", "void killObject()", asMETHOD(ScriptableObject, killObject), asCALL_THISCALL); assert(r >= 0);

		// Access the owning object through the script - getOwner returns the entity id
		r = scriptEngine->RegisterObjectMethod("ScriptableObject", "uint16 getOwner()", asMETHOD(ScriptableObject, getOwner), asCALL_THISCALL); assert(r >= 0);

		// The script can send a message to the other object through this method
		// Observe the autohandle @+ to tell AngelScript to automatically release the handle after the call
		// The generic handle type is used to allow the script to pass any object to
		// the other script without the application having to know anything about it
		r = scriptEngine->RegisterObjectMethod("ScriptableObject", "void sendMessage(ref message, const ScriptableObject @+ to)", asMETHOD(ScriptableObject, sendMessage), asCALL_THISCALL); assert(r >= 0);


		// The game engine will determine the class that represents the controller
		// by checking if the class implements the IController interface. No methods
		// are registered for this interface, as the script shouldn't be required to
		// implement the methods. This will allow the game engine to avoid calling
		// methods that doesn't do anything, thus improving performance.
		r = scriptEngine->RegisterInterface("IController"); assert(r >= 0);

		// InputHandler function handles.
		// Note that InputHandler provides only static functions which are registered as global functions.
		r = scriptEngine->RegisterGlobalFunction("bool IsKeyDown(uint)", asFUNCTION(IsKeyDown), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("bool IsMouseButtonDown(uint)", asFUNCTION(IsMouseButtonDown), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("float GetMouseX()", asFUNCTION(GetMouseX), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("float GetMouseY()", asFUNCTION(GetMouseY), asCALL_CDECL); assert(r >= 0);
		
		// Register glm types
		r = scriptEngine->RegisterObjectType("Vec2", sizeof(glm::vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Vec2", "float x", asOFFSET(glm::vec2, x)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Vec2", "float y", asOFFSET(glm::vec2, y)); assert(r >= 0);		
		
		r = scriptEngine->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vec2Default), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f(const Vec2 &in)", asFUNCTION(Vec2Copy), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(Vec2Init1), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(Vec2Init2), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opAddAssign(const Vec2& in) const", 
			asMETHODPR(glm::vec2, operator+=, (const glm::vec2 &), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opSubAssign(const Vec2& in) const",
			asMETHODPR(glm::vec2, operator-=, (const glm::vec2 &), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opMulAssign(const Vec2& in) const",
			asMETHODPR(glm::vec2, operator*=, (const glm::vec2 &), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opDivAssign(const Vec2& in) const",
			asMETHODPR(glm::vec2, operator/=, (const glm::vec2 &), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "bool opEquals(const Vec2& in) const",
			asFUNCTIONPR(glm::operator==, (const glm::vec2&, const glm::vec2&), bool), asCALL_CDECL_OBJFIRST); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 opAdd(const Vec2 &in) const",
			asFUNCTIONPR(glm::operator+, (const glm::vec2&, const glm::vec2&), glm::vec2), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 opSub(const Vec2 &in) const",
			asFUNCTIONPR(glm::operator-, (const glm::vec2&, const glm::vec2&), glm::vec2), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 opMul(const Vec2 &in) const",
			asFUNCTIONPR(glm::operator*, (const glm::vec2&, const glm::vec2&), glm::vec2), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 opDiv(const Vec2 &in) const",
			asFUNCTIONPR(glm::operator/, (const glm::vec2&, const glm::vec2&), glm::vec2), asCALL_CDECL_OBJFIRST); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opAddAssign(const float& in) const",
			asMETHODPR(glm::vec2, operator+=, (const float&), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opSubAssign(const float& in) const",
			asMETHODPR(glm::vec2, operator-=, (const float&), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opMulAssign(const float& in) const",
			asMETHODPR(glm::vec2, operator*=, (const float&), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opDivAssign(const float& in) const",
			asMETHODPR(glm::vec2, operator/=, (const float&), glm::vec2&), asCALL_THISCALL); assert(r >= 0);

		// Register the components. The scripts cannot create these directly, so there is no factory function.
		r = scriptEngine->RegisterObjectType("Transform", 0, asOBJ_REF); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Transform", asBEHAVE_ADDREF, "void f()", asMETHOD(Transform, addReference), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Transform", asBEHAVE_RELEASE, "void f()", asMETHOD(Transform, release), asCALL_THISCALL); assert(r >= 0);
		
		r = scriptEngine->RegisterGlobalFunction("Transform@ InitTransform()", asFUNCTION(Transform_Factory1), asCALL_CDECL); assert(r >= 0);
		
		r = scriptEngine->RegisterObjectProperty("Transform", "Vec2 position", asOFFSET(Transform, position)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Transform", "float rotation", asOFFSET(Transform, rotation)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Transform", "Vec2 scale", asOFFSET(Transform, scale)); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Transform", "Transform &opAssign(const Transform &in)", 
			asMETHODPR(Transform, operator=, (const Transform &), Transform &), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Transform", asBEHAVE_FACTORY, "Transform@ f()", asFUNCTION(Transform_Factory1), asCALL_CDECL); assert(r >= 0);
	
		
		// Register template specializations & factories for ECS methods
		r = scriptEngine->RegisterGlobalFunction("Transform@ FindTransform(uint16)", asFUNCTION(FindTransform), asCALL_CDECL); assert(r >= 0);

		return 0;
	}

	asIScriptObject* ScriptManager::createScriptController(const std::string& script, ScriptableObject* gameObject, Entity entity)
	{
		int asReturnValue;
		asIScriptObject* object = 0;

		SController* controller = getScriptController(script);
		if (controller == 0) 
			return 0;

		// Create the object using the factory function
		asIScriptContext* context = getScriptContextFromPool(controller->createFunction);

		// Pass the object pointer to the script function. With this call the 
		// context will automatically increase the reference count for the object.
		context->SetArgObject(0, gameObject);

		// Make the call and take care of any errors that may happen
		asReturnValue = callScript(context);
		if (asReturnValue == asEXECUTION_FINISHED)
		{
			// Get the newly created object
			object = *((asIScriptObject**)context->GetAddressOfReturnValue());

			// Since a reference will be kept to this object 
			// it is necessary to increase the ref count
			object->AddRef();
		}
		gameObject->setScriptObject(object);
		gameObject->setOwner(entity);

		// Return the context to the pool so it can be reused
		returnScriptContextToPool(context);

		return object;
	}

	void ScriptManager::callOnUpdate(asIScriptObject* scriptObject)	//, Timestep* ts
	{
		// Find the cached onThink method id
		SController *controller = reinterpret_cast<SController*>(scriptObject->GetObjectType()->GetUserData());	//scriptObject was nullptr

		// Call the method using the shared context
		if (controller->onUpdateMethod != 0)
		{
			//IVY_CORE_INFO("ScriptManager::callOnUpdate. scriptObject");
			asIScriptContext *context = getScriptContextFromPool(controller->onUpdateMethod);
			context->SetObject(scriptObject);
			//context->SetArgObject(0, &deltaTime);
			callScript(context);
			returnScriptContextToPool(context);
		}
	}

	void ScriptManager::setMessageCallback(const asSMessageInfo& message)
	{
		const char *type = "ERR ";
		if (message.type == asMSGTYPE_WARNING)
			type = "WARN";
		else if (message.type == asMSGTYPE_INFORMATION)
			type = "INFO";

		IVY_CORE_INFO("Message={4}, Section={0}, Position=({1},{2}), Type={3}", message.section, message.row, message.col, message.type, message.message);

		if (message.type == asMSGTYPE_ERROR)
			hasCompileErrors = true;
		IVY_CORE_INFO("HasCompileErrors={0}", hasCompileErrors);
	}

	asIScriptContext* ScriptManager::getScriptContextFromPool(asIScriptFunction* function)
	{
		asIScriptContext* context = 0;
		if (contextList.size())
		{
			context = *contextList.rbegin();
			contextList.pop_back();
		}
		else
			context = scriptEngine->CreateContext();

		int r = context->Prepare(function); 
		assert(r >= 0);

		return context;
	}

	void ScriptManager::returnScriptContextToPool(asIScriptContext* context)
	{
		contextList.push_back(context);

		// Unprepare the context to free any objects that might be held
		// as we don't know when the context will be used again.
		context->Unprepare();
	}

	int ScriptManager::callScript(asIScriptContext* context)
	{
		int success = context->Execute();
		if (success != asEXECUTION_FINISHED)
		{
			if (success == asEXECUTION_EXCEPTION)
			{
				IVY_CORE_ERROR("Exception: {0} \n Function: {1} \n Line: {2}",
					context->GetExceptionString(),
					context->GetExceptionFunction()->GetDeclaration(),
					context->GetExceptionLineNumber());
			}
		}

		return success;
	}

	ScriptManager::SController* ScriptManager::getScriptController(const std::string& script)
	{
		int asReturnValue;

		// Find the cached controller
		for (unsigned int i = 0; i < controllerList.size(); i++)
		{
			if (controllerList[i]->module == script)
				return controllerList[i];
		}

		// No controller found, check if the script has already been loaded
		asIScriptModule *module = scriptEngine->GetModule(script.c_str(), asGM_ONLY_IF_EXISTS);	
		if (module)
		{
			// We've already attempted loading the script before, but there is no controller
			return 0;
		}
		
		// Compile the script into the module
		CScriptBuilder builder;
		asReturnValue = builder.StartNewModule(scriptEngine, script.c_str());
		if (asReturnValue < 0)
			return 0;

		// If the script file doesn't exist, then there is no script controller for this type
		FILE* file;
		if ((file = fopen((script /*+ ".as"*/).c_str(), "r")) == 0)
			return 0;
		fclose(file);

		// Let the builder load the script, and do the necessary pre-processing (include files, etc)
		asReturnValue = builder.AddSectionFromFile((script /*+ ".as"*/).c_str());
		if (asReturnValue < 0)
			return 0;

		asReturnValue = builder.BuildModule();
		if (asReturnValue < 0)
			return 0;

		// Cache the functions and methods that will be used
		SController *controller = new SController;
		controllerList.push_back(controller);
		controller->module = script;

		// Find the class that implements the IController interface
		module = scriptEngine->GetModule(script.c_str(), asGM_ONLY_IF_EXISTS);
		asITypeInfo *type = 0;
		int typeCount = module->GetObjectTypeCount();
		for (int n = 0; n < typeCount; n++)
		{
			bool found = false;
			type = module->GetObjectTypeByIndex(n);
			int interfaceCount = type->GetInterfaceCount();
			for (int i = 0; i < interfaceCount; i++)
			{
				if (strcmp(type->GetInterface(i)->GetName(), "IController") == 0)
				{
					found = true;
					break;
				}
			}

			if (found == true)
			{
				controller->controllerType = type;
				break;
			}
		}

		if (controller->controllerType == 0)
		{
			IVY_CORE_ERROR("Couldn't find the controller class for the type '{0}'", script);
			controllerList.pop_back();
			delete controller;
			return 0;
		}

		// Find the factory function
		// The game engine will pass in the owning ScriptableObject to the controller for storage
		std::string s = std::string(type->GetName()) + "@ " + std::string(type->GetName()) + "(ScriptableObject @)";
		controller->createFunction = type->GetFactoryByDecl(s.c_str());
		if (controller->createFunction == 0)
		{
			IVY_CORE_ERROR("Couldn't find the appropriate factory for the type '{0}'", script);
			controllerList.pop_back();
			delete controller;
			return 0;
		}

		// Find the optional event handlers
		controller->onUpdateMethod = type->GetMethodByDecl("void onUpdate()");
		controller->onMessageMethod = type->GetMethodByDecl("void onMessage(ref @msg, const CGameObj @sender)");

		// Add the cache as user data to the type for quick access
		type->SetUserData(controller);

		return controller;
	}

	void ScriptManager::callOnMessage(asIScriptObject* scriptObject, CScriptHandle& message, ScriptableObject* caller)
	{
		// Find the cached onMessage method id
		SController* controller = reinterpret_cast<SController*>(scriptObject->GetObjectType()->GetUserData());

		// Call the method using the shared context
		if (controller->onMessageMethod != 0)
		{
			asIScriptContext* context = getScriptContextFromPool(controller->onMessageMethod);
			context->SetObject(scriptObject);
			context->SetArgObject(0, &message);
			context->SetArgObject(1, caller);
			callScript(context);
			returnScriptContextToPool(context);
		}
	}
}