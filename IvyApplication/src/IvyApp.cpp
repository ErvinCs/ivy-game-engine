#include <Ivy.h>
#include "Ivy/Core/EntryPoint.h"

#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

class GameLayer : public Ivy::SortingLayer
{
private:
public:
	GameLayer() : SortingLayer("Game")
	{
		IVY_TRACE("Creating GameLayer");
	}

	void update(Ivy::Timestep ts) override {}

	void imGuiRender() override {}

	void onEvent(Ivy::Event& event) override {}

	~GameLayer() {}
};

class IvyApp : public Ivy::Application
{
public:
	IvyApp()
	{
		pushLayer(new GameLayer());
	}

	~IvyApp()
	{

	}
};

Ivy::Application* Ivy::CreateApp()
{
	return new IvyApp();
}