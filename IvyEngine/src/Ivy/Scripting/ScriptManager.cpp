#include "ivypch.h"
#include "ScriptManager.h"

#include <new>
#include "ASRegistrationCalls.h"
#include "../angelscript/add_on/scriptstdstring/scriptstdstring.h"
#include "../angelscript/add_on/scriptbuilder/scriptbuilder.h"
#include "../angelscript/add_on/weakref/weakref.h"
#include "../Core/Logger.h"

namespace Ivy {

	ScriptManager::~ScriptManager()
	{
		for (unsigned int n = 0; n < controllerList.size(); n++)
			delete controllerList[n];

		for (unsigned int n = 0; n < contextList.size(); n++)
			contextList[n]->Release();

		scriptEngine->GarbageCollect(asGC_FULL_CYCLE);

		if (scriptEngine)
			scriptEngine->ShutDownAndRelease();

		scriptEngine = 0;
	}

	int ScriptManager::init()
	{
		IVY_CORE_INFO("ScriptManager: Initializing ScriptManager Engine");
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

		// Register deltaTime. Currently a float variable.
		RegisterTimestep(scriptEngine);

		// Register InputHandler function handles. Note that InputHandler provides only static functions which are registered as global functions.
		RegisterInputHandler(scriptEngine);

		// Register Vec2 GLM Type
		RegisterVec2(scriptEngine);

		// The scripts cannot create these directly, so there is no factory function:
		// Register the Transform component
		RegisterTransform(scriptEngine);

		// Register the Sprite component
		RegisterRenderable(scriptEngine);

		// Register collision checking
		RegisterCollision(scriptEngine);

		// Register ScriptableObject
		RegisterScriptableObject(scriptEngine);

		// The game engine will determine the class that represents the controller by checking if the class implements the IController interface. 
		// No methods are registered for this interface, as the script shouldn't be required to implement the methods. 
		// This will allow the game engine to avoid calling methods that don't do anything, improving performance.
		r = scriptEngine->RegisterInterface("IController"); assert(r >= 0);

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

		// Pass the object pointer to the script function.
		// With this call the context will automatically increase the reference count for the object.
		context->SetArgObject(0, gameObject);

		// Make the call and take care of any errors that may happen
		asReturnValue = callScript(context);
		if (asReturnValue == asEXECUTION_FINISHED)
		{
			// Get the newly created object
			object = *((asIScriptObject**)context->GetAddressOfReturnValue());

			// Since a reference will be kept to this object it is necessary to increase the ref count
			object->AddRef();
		}
		gameObject->setScriptObject(object);
		gameObject->setOwner(entity);

		// Return the context to the pool so it can be reused
		returnScriptContextToPool(context);

		IVY_CORE_INFO("ScriptManager: Creating ScriptController: name={0}, entity={1}", gameObject->getName(), entity);

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
		{
			type = "WARN";
			IVY_CORE_WARN("ScriptManager: Message={4}, Section={0}, Position=({1},{2}), Type={3}", message.section, message.row, message.col, message.type, message.message);
		}
		else if (message.type == asMSGTYPE_INFORMATION)
		{
			type = "INFO";
			IVY_CORE_WARN("ScriptManager: Message={4}, Section={0}, Position=({1},{2}), Type={3}", message.section, message.row, message.col, message.type, message.message);
		}

		if (message.type == asMSGTYPE_ERROR)
			hasCompileErrors = true;
		IVY_CORE_WARN("ScriptManager: HasCompileErrors={0}", hasCompileErrors);
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

		// Unprepare the context to free any objects that might be held  as we don't know when the context will be used again.
		context->Unprepare();
	}

	int ScriptManager::callScript(asIScriptContext* context)
	{
		int success = context->Execute();
		if (success != asEXECUTION_FINISHED)
		{
			if (success == asEXECUTION_EXCEPTION)
			{
				IVY_CORE_ERROR("ScriptManager: CallScript: Exception: {0} \n Function: {1} \n Line: {2}",
					context->GetExceptionString(),
					context->GetExceptionFunction()->GetDeclaration(),
					context->GetExceptionLineNumber());
			}
		}

		return success;
	}

	ScriptManager::SController* ScriptManager::getScriptController(const std::string& script)
	{
		IVY_CORE_TRACE("ScriptManager: GetScriptController: name={0}", script);
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
		if ((file = fopen((script).c_str(), "r")) == 0)
			return 0;
		fclose(file);

		// Let the builder load the script, and do the necessary pre-processing (include files, etc)
		asReturnValue = builder.AddSectionFromFile((script).c_str());
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
			IVY_CORE_ERROR("ScriptManager: Couldn't find the controller class for the type '{0}'", script);
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
			IVY_CORE_ERROR("ScriptManager: Couldn't find the appropriate factory for the type '{0}'", script);
			controllerList.pop_back();
			delete controller;
			return 0;
		}

		// Find the optional event handlers
		controller->onUpdateMethod = type->GetMethodByDecl("void onUpdate()");
		controller->onMessageMethod = type->GetMethodByDecl("void onMessage(ref @message, const ScriptableObject @sender)");

		// Add the cache as user data to the type for quick access
		type->SetUserData(controller);

		return controller;
	}

	void ScriptManager::callOnMessage(asIScriptObject* scriptObject, CScriptHandle& message, ScriptableObject* caller)
	{
		IVY_CORE_TRACE("ScriptManager: CallOnMessage");
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