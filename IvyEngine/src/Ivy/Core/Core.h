#pragma once

#ifdef IVY_PLATFORM_WINDOWS
	#ifdef IVY_BUILD_DLL
		#define IVY_API __declspec(dllexport)
	#else
		#define IVY_API __declspec(dllimport)
	#endif
#else
	#error Only Windows is supported!
#endif
