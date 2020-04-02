#include <Ivy.h>

#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"



/* TODOs
 - Remove hardcoded strings - use <filesystem>
 - Move all assets (except shaders) to engine side and fix paths accordingly
 - Asset Import
	- When creating a new Renderable or Script allow user to pick a file anywhere on his computer 
	- Use <filesystem> to copy that file into res and store a reference to that copy
 - Collision System ( + Events )
 - PCG Module

 - Remove Explicit camera creation from IvyApp - Move it to engine side and allow acces to it
 - Move ImGui code to the engine side 
	- Create a new layer for Component Management Menu
	- Create a new layer for PCG Menu
 - Place entities on Rendering Sorting Layers
 - Remove Explicit system init from IvyApp - Move it to engine side
 - Centralize Component IDs

 - Prompt before terminating application & Auto-save state on shutdown
 - Enable AngelScript Leak Checking ( in EntryPoint )
 - Move AngelScript bind calls to separate files
 - Clean & Refactor Renderer
 - Fix JSONManager & Renderer issues
*/

class TestLayer : public Ivy::SortingLayer
{
private:
	// These can probably be moved into the Menu Layer or in ECS
	//ECS getECS = &Ivy::ECS::getInstance;

	//Systems
	std::shared_ptr<Ivy::System> renderSystem = std::make_shared<Ivy::RenderSystem>(Ivy::ECS::getInstance().getEntities());
	std::shared_ptr<Ivy::System> scriptSystem = std::make_shared<Ivy::ScriptSystem>(Ivy::ECS::getInstance().getEntities());

private:
	//Camera
	Ivy::OrthoCamera camera;

	// Screen Borders - Used for ImGui
	float leftBorder = 12.3f;
	float rightBorder = -11.8f;
	float topBorder = 6.4f;
	float botBorder = -6.4f;

public:
	TestLayer() : SortingLayer("Test"), camera(-12.8f, 12.8f, -6.4f, 6.4f)
	{
		IVY_TRACE("Creating TestLayer");
		
		Ivy::ECS::getInstance().loadEntities();

		Ivy::ECS::getInstance().addSystem(renderSystem);
		Ivy::ECS::getInstance().addSystem(scriptSystem);

		renderSystem->init();
		scriptSystem->init();		
	}

	void update(Ivy::Timestep ts) override
	{
		// Render
		Ivy::RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		Ivy::RenderCommand::clear();
		Ivy::Renderer::Begin(camera);
		renderSystem->update(ts);
		Ivy::Renderer::End();

		// Script
		scriptSystem->update(ts);
	}

	void imGuiRender() override
	{
		
	}

	void onEvent(Ivy::Event& event) override
	{
		IVY_INFO("Test Layer: {0}", event.toString());
	}

	~TestLayer()
	{
	}
};

class IvyApp : public Ivy::Application
{
public:
	IvyApp()
	{
		pushLayer(new TestLayer());
	}

	~IvyApp()
	{

	}
};


Ivy::Application* Ivy::CreateApp()
{
	return new IvyApp();
}

