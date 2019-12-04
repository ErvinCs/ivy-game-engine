#pragma once

// Leave this here - 'not a class or namespace name' fix
#include "Application.h"

#ifdef IVY_PLATFORM_WINDOWS

// Will return an application from IvyApp in IvyApplication project
extern Ivy::Application* Ivy::CreateApp();

// Need some system initialization to init subsystems: Logger
int main(int argc, char** argv)
{
	Ivy::Logger::Init();
	IVY_CORE_WARN("Initialized Core Logger!");
	IVY_INFO("Initialized Client Logger!");

	auto application = Ivy::CreateApp();
	application->Init();
	application->Run();
	application->Shutdown();
	delete application;

	return 0;
}

#endif