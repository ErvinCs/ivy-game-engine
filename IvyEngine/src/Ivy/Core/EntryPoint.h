#pragma once

#ifdef IVY_PLATFORM_WINDOWS

// Will return an application from IvyApp in IvyApplication project
extern Ivy::Application* Ivy::CreateApplication();

// Need some system initialization to init subsystems: Logger
int main(int argc, char** argv)
{
	Ivy::Logger::Init();
	IVY_CORE_WARN("Initialized Core Logger!");
	IVY_INFO("Initialized Client Logger!");

	auto application = Ivy::CreateApplication();
	application->Init();
	application->Run();
	application->Shutdown();
	delete application;

}

#endif