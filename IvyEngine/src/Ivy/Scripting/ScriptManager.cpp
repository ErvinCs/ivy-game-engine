#include "ivypch.h"
#include "ScriptManager.h"

#include "../Core/Logger.h"

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

		// Register the game object. The scripts cannot create these directly, so there is no factory function.
		r = scriptEngine->RegisterObjectType("GameObject", 0, asOBJ_REF); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("GameObject", asBEHAVE_ADDREF, "void f()", asMETHOD(GameObject, addReference), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("GameObject", asBEHAVE_RELEASE, "void f()", asMETHOD(GameObject, release), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("GameObject", asBEHAVE_GET_WEAKREF_FLAG, "int &f()", asMETHOD(GameObject, getWeakRefereneFlag), asCALL_THISCALL); assert(r >= 0);

		// The object's position is read-only to the script. The position is updated with the Move method
		//r = scriptEngine->RegisterObjectMethod("GameObject", "int get_x() const", asMETHOD(GameObject, getX), asCALL_THISCALL); assert(r >= 0);
		//r = scriptEngine->RegisterObjectMethod("GameObject", "int get_y() const", asMETHOD(GameObject, getY), asCALL_THISCALL); assert(r >= 0);
		//r = scriptEngine->RegisterObjectMethod("GameObject", "bool Move(int dx, int dy)", asMETHOD(GameObject, Move), asCALL_THISCALL); assert(r >= 0);

		// The script can kill the owning object
		r = scriptEngine->RegisterObjectMethod("GameObject", "void killObject()", asMETHOD(GameObject, killObject), asCALL_THISCALL); assert(r >= 0);

		// The script can send a message to the other object through this method
		// Observe the autohandle @+ to tell AngelScript to automatically release the handle after the call
		// The generic handle type is used to allow the script to pass any object to
		// the other script without the application having to know anything about it
		r = scriptEngine->RegisterObjectMethod("GameObject", "void sendMessage(ref message, const GameObject @+ to)", asMETHOD(GameObject, sendMessage), asCALL_THISCALL); assert(r >= 0);


		// The game engine will determine the class that represents the controller
		// by checking if the class implements the IController interface. No methods
		// are registered for this interface, as the script shouldn't be required to
		// implement the methods. This will allow the game engine to avoid calling
		// methods that doesn't do anything, thus improving performance.
		r = scriptEngine->RegisterInterface("IController"); assert(r >= 0);

		/*
		// Register the game manager as a singleton. The script will access it through the global property
		r = scriptEngine->RegisterObjectType("GameManager", 0, asOBJ_REF | asOBJ_NOHANDLE); assert(r >= 0);

		// Register the game manager's methods
		r = scriptEngine->RegisterGlobalProperty("GameManager game", gameMgr); assert(r >= 0);

		// The script can determine what the user wants to do through the actionStates
		r = scriptEngine->RegisterObjectMethod("GameManager", "bool get_actionState(int idx)", asMETHOD(CGameMgr, GetActionState), asCALL_THISCALL); assert(r >= 0);

		// The script can call this method to end the game
		r = scriptEngine->RegisterObjectMethod("GameManager", "void EndGame(bool win)", asMETHOD(CGameMgr, EndGame), asCALL_THISCALL); assert(r >= 0);

		// Register a method that will allow the script to find an object by its name.
		// This returns the object as const handle, as the script should only be 
		// allow to directly modify its owner object.
		// Observe the @+ that tells AngelScript to automatically increase the refcount
		r = scriptEngine->RegisterObjectMethod("GameManager", "const CGameObj @+ FindObjByName(const string &in name)", asMETHOD(CGameMgr, FindGameObjByName), asCALL_THISCALL); assert(r >= 0);
		*/

		return 0;
	}

	asIScriptObject* ScriptManager::createScriptController(const std::string& script, GameObject* gameObject)
	{
		int asReturnValue;
		asIScriptObject *object = 0;

		SController *controller = getScriptController(script);
		if (controller == 0) 
			return 0;

		// Create the object using the factory function
		asIScriptContext *context = getScriptContextFromPool(controller->createFunction);

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

		// Return the context to the pool so it can be reused
		returnScriptContextToPool(context);

		return object;
	}

	void ScriptManager::callOnUpdate(asIScriptObject* scriptObject)
	{
		// Find the cached onThink method id
		SController *controller = reinterpret_cast<SController*>(scriptObject->GetObjectType()->GetUserData());

		// Call the method using the shared context
		if (controller->onUpdateMethod != 0)
		{
			asIScriptContext *context = getScriptContextFromPool(controller->onUpdateMethod);
			context->SetObject(scriptObject);
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
		if ((file = fopen((script + ".as").c_str(), "asReturnValue")) == 0)
			return 0;
		fclose(file);

		// Let the builder load the script, and do the necessary pre-processing (include files, etc)
		asReturnValue = builder.AddSectionFromFile((script + ".as").c_str());
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
		// The game engine will pass in the owning CGameObj to the controller for storage
		std::string s = std::string(type->GetName()) + "@ " + std::string(type->GetName()) + "(CGameObj @)";
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
		//controller->onMessageMethod = type->GetMethodByDecl("void OnMessage(ref @msg, const CGameObj @sender)");

		// Add the cache as user data to the type for quick access
		type->SetUserData(controller);

		return controller;
	}

	void ScriptManager::callOnMessage(asIScriptObject* scriptObject, CScriptHandle& message, GameObject* caller)
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