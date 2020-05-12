#pragma once

// Platform
#ifdef _WIN32
	// Windows x64/x86 
	#ifdef _WIN64
		// Windows x64  
		#define IVY_PLATFORM_WINDOWS
	#else
		// Windows x86
		#error "x86 Builds are not supported!"
	#endif
#endif

// Assertion mechanism. Cause a breakpoint if the expression in question is false.
#ifdef IVY_ENABLE_ASSERTS
	#define IVY_ASSERT(x, ...) { if(!(x)) { IVY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define IVY_CORE_ASSERT(x, ...) { if(!(x)) { IVY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define IVY_ASSERT(x, ...)
	#define IVY_CORE_ASSERT(x, ...)
#endif

