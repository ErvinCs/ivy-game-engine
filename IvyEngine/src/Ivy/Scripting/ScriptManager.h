#pragma once

#include <glm/glm.hpp>
#include <angelscript.h>
#include "../angelscript/add_on/scripthandle/scripthandle.h"
#include "../angelscript/add_on/scriptstdstring/scriptstdstring.h"
#include "../angelscript/add_on/scriptbuilder/scriptbuilder.h"
#include "../angelscript/add_on/weakref/weakref.h"
#include "ScriptableObject.h"

namespace Ivy {

	/**
	 * The ScriptManager is in charge of maintaing references to as well as creating script execution contexts and script controllers.
	 * It keeps pointers to the script functions and allows control of the garbage collector.
	 */
	class ScriptManager
	{
	protected:
		/**
		 * Contains information about a script module.
		 * The name of the module, its controller, and function pointers to all the functions
		 *  in the module are aggregated here.
		 */
		struct SController
		{
			SController() : controllerType(0), createFunction(0), onUpdateMethod(0), onMessageMethod(0) {}
			// Name of the script module
			std::string module;
			// Stores the controller type (maintained internally by the script negine)
			asITypeInfo* controllerType;
			// Factory function for `ScriptableObject`s
			asIScriptFunction* createFunction;
			// OnUpdate method for `ScriptableObject`s
			// Called every frame
			asIScriptFunction* onUpdateMethod;
			// OnMessage method for `ScriptableObject`s
			// Called on reveiving a message from another script
			asIScriptFunction* onMessageMethod;
		};

		// True if compile-time errors were detected in AS scripts and false otherwise
		bool hasCompileErrors;
		// Points to the script engine instance
		// The script engine registers the application interface, builds scripts and executes them
		asIScriptEngine* scriptEngine;
		// Stores pointers to the script execution contexts of the registered scripts.
		// Maintains the call stack
		std::vector<asIScriptContext*> contextList;
		std::vector<SController*> controllerList;

	public:
		static ScriptManager& GetInstance()
		{
			static ScriptManager instance{};
			return instance;
		}

		/**
		 * Releases contexts, destroys script controllers, runs the garbage collecter 
		 *  and finally shuts down the script engine
		 */
		~ScriptManager();

		/**
		 * Register with the script engine the available interfaces, types and methods.
		 * @see ASRegistrationCalls
		 */
		int init();

		/**
		 * Create a new script controller for a `ScriptableObject`, adds it to the pool and sets its reference count.
		 * @param script the name of the script file; it will be used to create an `SController`
		 * @param gameObject ScriptableObject associated with an Entity
		 * @param entity Entity which will be controlled by the created controller through the `ScriptComponent`
		 * @returns asIScriptObject* pointer to the beginning of the script
		 * @see SController
		 * @see ScriptComponent
		 */
		asIScriptObject* createScriptController(const std::string& script, ScriptableObject* gameObject, Entity entity);
		
		/*
		 * Performs garbage collection according to the option parameter.
		 * @param option int that determines the type of garbage collection ot be executed
		 *  option = 1 - One Step incremental collection
		 *  option = 2 - Full Cycle collection
		 */
		void garbageCollect(int option);

		/**
		 * Gets the controller and context of the script object and calls the onUpdate methdod
		 */
		void callOnUpdate(asIScriptObject* scriptObject);

		/**
		 * Gets the controller and context of the script object and calls the onMessage method
		 */
		void callOnMessage(asIScriptObject* scriptObject, CScriptHandle& message, ScriptableObject* caller);

		/**
		 * @returns true if compile errors have been detected in a script in the current context and false otherwise
		 */
		inline bool getHasCompileErrors() { return hasCompileErrors; }

		/**
		 * @returns asIScriptEngine* pointer to the script engine
		 */
		inline asIScriptEngine* getScriptEngine() { return this->scriptEngine; }
	protected:

		/**
		 * Set a message to be logged on errors or warnings.
		 * @param message string to be printed in the consoler
		 */
		void setMessageCallback(const asSMessageInfo& message);

		/**
		 * Prepares a method or a function of a script to be executed in the script execution phase.
		 * If the execution context exists then it is retrieved from `contextList`
		 * If the execution context does not exist a new one is created
		 * @returns asIScriptContex* points to the execution context in which `function` will be called
		 */
		asIScriptContext* getScriptContextFromPool(asIScriptFunction* function);

		/**
		 * Pushes into `contextList` a script context that was used in some earlier stage to execute a script.
		 * @param context to be returned to the context pool
		 */
		void returnScriptContextToPool(asIScriptContext* context);

		/**
		 * Executes the script associated to `context`. 
		 * If errors are present they are signaled and the script execution is stopped
		 * @param context asIScriptContext* the script execution context
		 * @returns int 0 if no errors are encountered and an integer greater than 0 otherwise
		 */
		int callScript(asIScriptContext* context);

		/**
		 * Find a stored script controller with the given name.
		 * @returns SController* a pointer to the script controller stored in the `controllerList`
		 *  that has the name `script`. If the script controller does not exists, returns 0.
		 */
		SController* getScriptController(const std::string& script);

		// Base Constructor. Creates a null script engine.
		ScriptManager()
		{
			scriptEngine = 0;
			hasCompileErrors = false;
		}

		ScriptManager(const ScriptManager&) = delete;
		ScriptManager& operator=(const ScriptManager&) = delete;
	};

}