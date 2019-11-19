#include <Ivy.h>

//TODO
/*class TestLayer : public Ivy::SortingLayer
{
public:
	TestLayer() : SortingLayer("Test") {}

	void update() override
	{
		IVY_INFO("TestLayer Client Update.");
	}

	void onEvent(Ivy::Event& event) override
	{
		IVY_INFO("Event: {0}", event.toString());
	}
};*/

class IvyApp : public Ivy::Application
{
public:
	IvyApp()
	{
		//pushLayer(new TestLayer());
		//pushLayer(new Ivy::ImGuiLayer());
	}

	~IvyApp()
	{

	}
};


Ivy::Application* Ivy::CreateApp()
{
	return new IvyApp();
}