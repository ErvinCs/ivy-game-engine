#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Ivy {

	class IVY_API Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return coreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return clientLogger;
		}
	};

}

// TODO - Other macros that would use Error, Warn etc, only under certain circumstances

// Core Logger
#define IVY_CORE_FATAL(...) ::Ivy::Logger::GetCoreLogger()->fatal(__VA_ARGS__)
#define IVY_CORE_ERROR(...) ::Ivy::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define IVY_CORE_WARN(...)  ::Ivy::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define IVY_CORE_INFO(...)  ::Ivy::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define IVY_CORE_TRACE(...) ::Ivy::Logger::GetCoreLogger()->trace(__VA_ARGS__)

// Client Logger
#define IVY_FATAL(...) ::Ivy::Logger::GetClientLogger()->fatal(__VA_ARGS__)
#define IVY_ERROR(...) ::Ivy::Logger::GetClientLogger()->error(__VA_ARGS__)
#define IVY_WARN(...)  ::Ivy::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define IVY_INFO(...)  ::Ivy::Logger::GetClientLogger()->info(__VA_ARGS__)
#define IVY_TRACE(...) ::Ivy::Logger::GetClientLogger()->trace(__VA_ARGS__)

// Strap Logs from distribution build
#define IVY_CORE_INFO