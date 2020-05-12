#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Ivy {

	/**
	 * Static class that provides access to the engine logger and application logger.
	 *	coreLogger   - used to log engine operations
	 *  clientLogger - used to log application operations
	 */
	class Logger
	{
	private:
		// Engine logger
		static std::shared_ptr<spdlog::logger> coreLogger;
		// Application logger
		static std::shared_ptr<spdlog::logger> clientLogger;

	public:
		/**
		 * Initialize the patterns and color codes for the engine & client loggers
		 */
		static void Init();

		// Get the engine logger
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return coreLogger;
		}

		// Get the application logger
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return clientLogger;
		}
	};

}

// Core Logger Settings
#define IVY_CORE_FATAL(...) ::Ivy::Logger::GetCoreLogger()->fatal(__VA_ARGS__)	//Severe errors that lead to application abort
#define IVY_CORE_ERROR(...) ::Ivy::Logger::GetCoreLogger()->error(__VA_ARGS__)	//Error events that might still allow the application to run
#define IVY_CORE_WARN(...)  ::Ivy::Logger::GetCoreLogger()->warn(__VA_ARGS__)	//Highlight potentionally harmful situations 
#define IVY_CORE_INFO(...)  ::Ivy::Logger::GetCoreLogger()->info(__VA_ARGS__)	//General informational messages - Used to track application progress  
#define IVY_CORE_TRACE(...) ::Ivy::Logger::GetCoreLogger()->trace(__VA_ARGS__)	//Fine-Grained informational events - Used for debugging

// Client Logger Settings
#define IVY_FATAL(...) ::Ivy::Logger::GetClientLogger()->fatal(__VA_ARGS__)		//Severe errors that lead to application abort
#define IVY_ERROR(...) ::Ivy::Logger::GetClientLogger()->error(__VA_ARGS__)		//Error events that might still allow the application to run
#define IVY_WARN(...)  ::Ivy::Logger::GetClientLogger()->warn(__VA_ARGS__)		//Highlight potentionally harmful situations 
#define IVY_INFO(...)  ::Ivy::Logger::GetClientLogger()->info(__VA_ARGS__)		//General informational messages - Used to track application progress 
#define IVY_TRACE(...) ::Ivy::Logger::GetClientLogger()->trace(__VA_ARGS__)		//Fine-Grained informational events - Used for debugging

// Strip engine-side Logs from distribution build
#ifdef _DEBUG
#else
#define IVY_CORE_INFO
#define IVY_CORE_TRACE
#define IVY_CORE_WARN
#define IVY_CORE_ERROR
#define IVY_CORE_FATAL
#endif
