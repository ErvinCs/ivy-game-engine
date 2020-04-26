#pragma once

// Leave this here - 'not a class or namespace name' fix
#include "Application.h"

#ifdef IVY_PLATFORM_WINDOWS
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

// Return an application from IvyApp in IvyApplication project
extern Ivy::Application* Ivy::CreateApp();

// Initialize subsystems: Logger
int main(int argc, char** argv)
{
#ifdef _DEBUG
	#ifdef _MSC_VER
		// Detect memory leaks
		#define _CRTDBG_MAP_ALLOC
		#include <cstdlib>
		#include <crtdbg.h>
		#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
		_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
		//_CrtSetBreakAlloc(n) to find a specific memory leak
	#endif
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	#else
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	#define DBG_NEW new
#endif
	

	Ivy::Logger::Init();
	IVY_CORE_WARN("Initialized Core Logger!");
	IVY_INFO("Initialized Client Logger!");

	auto application = Ivy::CreateApp();
	application->init();
	application->run();
	application->shutdown();
	delete application;

#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
#endif

	return 0;
}

#endif