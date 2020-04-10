#pragma once

// Leave this here - 'not a class or namespace name' fix
#include "Application.h"

#ifdef IVY_PLATFORM_WINDOWS

// Return an application from IvyApp in IvyApplication project
extern Ivy::Application* Ivy::CreateApp();

// Initialize subsystems: Logger
int main(int argc, char** argv)
{
#ifdef _MSC_VER
	// Detect memory leaks
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	// Use _CrtSetBreakAlloc(n) to find a specific memory leak
#endif

	Ivy::Logger::Init();
	IVY_CORE_WARN("Initialized Core Logger!");
	IVY_INFO("Initialized Client Logger!");

	// TODO - Somewhere in here the NEW/LOAD PROJECT functionality should be called

	auto application = Ivy::CreateApp();
	application->init();
	application->run();
	application->shutdown();
	delete application;

	return 0;
}

#endif