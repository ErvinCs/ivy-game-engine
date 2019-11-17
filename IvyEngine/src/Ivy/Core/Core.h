#pragma once


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

#ifdef IVY_ENABLE_ASSERTS
	#define IVY_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define IVY_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define IVY_ASSERT(x, ...)
	#define IVY_CORE_ASSERT(x, ...)
#endif

#define IVY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// Deprecated: Not using DLLs anymore
/*#ifdef IVY_PLATFORM_WINDOWS
	#ifdef IVY_BUILD_DLL
		#define IVY_API __declspec(dllexport)
	#else
		#define IVY_API __declspec(dllimport)
	#endif
#else
	#error Only Windows is supported!
#endif*/

