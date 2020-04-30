#include <Ivy.h>
#include "Ivy/Core/EntryPoint.h"

#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

#include "UserComponent.h"

class GameLayer : public Ivy::SortingLayer
{
private:
	//Systems
	//std::shared_ptr<Ivy::System> userSystem      = std::make_shared<UserComponentSystem>(Ivy::ECS::getInstance().getEntities());

	bool isStarted = false, isPaused = false, isLoaded = false, loadedMenu = false;
	Entity mainMenu, pauseMenu;
public:
	GameLayer() : SortingLayer("Game")
	{
		IVY_TRACE("Creating GameLayer");

		//Ivy::ECS::getInstance().addSystem(userSystem);

		//userSystem->init();

		mainMenu = Ivy::ECS::getInstance().createEntity();
		Ivy::ECS::getInstance().addComponent<Ivy::Renderable>(mainMenu, Ivy::Renderable("level-complete.png"));
		pauseMenu = Ivy::ECS::getInstance().createEntity();
		Ivy::ECS::getInstance().addComponent<Ivy::Renderable>(pauseMenu, Ivy::Renderable("level-complete.png"));
		
	}

	void update(Ivy::Timestep ts) override
	{
		// User System
		//userSystem->update(ts);
		if (isLoaded)
		{
			if (!isStarted) 
			{
				Ivy::Application::getInstance().isPaused = true;
				if (!loadedMenu)
				{
					Ivy::ECS::getInstance().addComponent<Ivy::Transform>(mainMenu, Ivy::Transform(Ivy::Application::GetCamera().position, 0.0f, glm::vec2(4.0f, 4.0f)));
					loadedMenu = true;
				}
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_SPACE))
				{
					Ivy::ECS::getInstance().removeComponent<Ivy::Transform>(pauseMenu);
					isStarted = true;
					loadedMenu = false;
					Ivy::Application::getInstance().isPaused = false;
				}
			}


			if (Ivy::InputHandler::IsKeyDown(IVY_KEY_P) && isStarted)
			{
				isPaused = true;
				Ivy::Application::getInstance().isPaused = true;
			}
			if (isPaused)
			{
				if (!loadedMenu)
				{
					Ivy::ECS::getInstance().addComponent<Ivy::Transform>(pauseMenu, Ivy::Transform(Ivy::Application::GetCamera().position, 0.0f, glm::vec2(4.0f, 4.0f)));
					loadedMenu = true;
				}
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_X))
				{
					Ivy::Application::getInstance().isRunning = false;
				}
				else if (Ivy::InputHandler::IsKeyDown(IVY_KEY_C))
				{
					Ivy::ECS::getInstance().removeComponent<Ivy::Transform>(pauseMenu);
					isPaused = false;
					Ivy::Application::getInstance().isPaused = false;
				}
			}
		}
		else
		{
			Ivy::Application::getInstance().globalTime = 0.0f;
			Ivy::Application::GetLevelGenerator().run();
			Ivy::Application::getInstance().lastFrameTime = (float)glfwGetTime();
			isLoaded = true;
		}
	}

	void imGuiRender() override
	{

	}

	void onEvent(Ivy::Event& event) override
	{
		IVY_INFO("Test Layer: {0}", event.toString());
	}

	~GameLayer()
	{
	}
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

