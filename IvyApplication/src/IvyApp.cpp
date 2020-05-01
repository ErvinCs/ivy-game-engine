#include <Ivy.h>
#include "Ivy/Core/EntryPoint.h"

#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

#include "UserComponent.h"

class GameLayer : public Ivy::SortingLayer
{
private:
	bool isStarted = false, isLoaded = false, loadedMenu = false;
	glm::vec2 menuSize = glm::vec2(7.0f, 7.0f);
	Entity mainMenu;
	//Entity pauseMenu, victoryMenu;
	const int final_score = 11;
	static int level_score;
public:
	GameLayer() : SortingLayer("Game")
	{
		IVY_TRACE("Creating GameLayer");

		mainMenu = Ivy::ECS::getInstance().createEntity();
		Ivy::ECS::getInstance().addComponent<Ivy::Renderable>(mainMenu, Ivy::Renderable("level-menu.png"));
		//pauseMenu = Ivy::ECS::getInstance().createEntity();
		//Ivy::ECS::getInstance().addComponent<Ivy::Renderable>(pauseMenu, Ivy::Renderable("level-paused.png"));
		//victoryMenu = Ivy::ECS::getInstance().createEntity();
		//Ivy::ECS::getInstance().addComponent<Ivy::Renderable>(pauseMenu, Ivy::Renderable("level-won.png"));

		int r = Ivy::ScriptManager::GetInstance().getScriptEngine()->RegisterGlobalProperty("int level_score", &level_score); assert(r >= 0);
	}

	void update(Ivy::Timestep ts) override
	{
		if (isLoaded)
		{
			if (!isStarted) 
			{
				Ivy::Application::getInstance().isPaused = true;
				if (!loadedMenu)
				{
					Ivy::ECS::getInstance().addComponent<Ivy::Transform>(mainMenu, Ivy::Transform(Ivy::Application::GetCamera().position, 0.0f, menuSize));
					loadedMenu = true;
				}
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_X))
				{
					Ivy::ECS::getInstance().clearECS();
					Ivy::ScriptManager::GetInstance().garbageCollect(2);
					Ivy::Application::getInstance().isRunning = false;
				}
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_SPACE))
				{
					Ivy::ECS::getInstance().removeComponent<Ivy::Transform>(mainMenu);
					isStarted = true;
					Ivy::Application::getInstance().isPaused = false;
					loadedMenu = false;
				}
			}


			if (Ivy::InputHandler::IsKeyDown(IVY_KEY_P) && isStarted)
			{
				Ivy::Application::getInstance().isPaused = true;
			}
			if (Ivy::Application::getInstance().isPaused)
			{
				if (!loadedMenu)
				{
					Ivy::ECS::getInstance().addComponent<Ivy::Transform>(mainMenu, Ivy::Transform(Ivy::Application::GetCamera().position, 0.0f, menuSize));
					loadedMenu = true;
				}
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_X))
				{
					Ivy::ECS::getInstance().clearECS();
					Ivy::ScriptManager::GetInstance().garbageCollect(2);		
					Ivy::Application::getInstance().isRunning = false;
				}
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_SPACE))
				{
					Ivy::ECS::getInstance().removeComponent<Ivy::Transform>(mainMenu);
					Ivy::Application::getInstance().isPaused = false;
					loadedMenu = false;
				}
			}
		}
		else
		{
			Ivy::Application::getInstance().isPaused = true;
			Ivy::Application::GetLevelGenerator().run();
			isLoaded = true;
		}

		if (level_score == final_score)
		{
			isStarted = false; isLoaded = false; loadedMenu = false;
			Ivy::ECS::getInstance().clearECS();
			Ivy::ScriptManager::GetInstance().garbageCollect(2);
			level_score = 0;
			mainMenu = Ivy::ECS::getInstance().createEntity();
			Ivy::ECS::getInstance().addComponent<Ivy::Renderable>(mainMenu, Ivy::Renderable("level-menu.png"));
			//pauseMenu = Ivy::ECS::getInstance().createEntity();
			//Ivy::ECS::getInstance().addComponent<Ivy::Renderable>(pauseMenu, Ivy::Renderable("level-paused.png"));
		}

		Ivy::ScriptManager::GetInstance().garbageCollect(1);
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

int GameLayer::level_score = 0;

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

