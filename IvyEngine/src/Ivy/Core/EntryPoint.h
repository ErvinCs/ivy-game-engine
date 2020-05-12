#pragma once

#include "Application.h"

// Main loop on Windows
#ifdef IVY_PLATFORM_WINDOWS
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

// Return an application from IvyApp in IvyApplication project
extern Ivy::Application* Ivy::CreateApp();

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
	#endif
	// Show the console in Debug builds
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	#else
	// Hide the console in Release builds
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	#define DBG_NEW new
#endif
	
	// Initialize Loggers
	Ivy::Logger::Init();
	IVY_CORE_WARN("Initialized Core Logger!");
	IVY_INFO("Initialized Client Logger!");

	// Run the Application
	auto application = Ivy::CreateApp();
	application->init();
	application->run();
	application->shutdown();
	delete application;

	return 0;
}
#endif