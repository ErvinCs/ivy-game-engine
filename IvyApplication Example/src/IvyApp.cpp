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
	const int final_score = 11;
	static int level_score;
public:
	GameLayer() : SortingLayer("Game")
	{
		IVY_TRACE("Creating GameLayer");

		// Create the Menu Entity
		mainMenu = Ivy::ECS::getInstance().createEntity();
		Ivy::ECS::getInstance().addComponent<Ivy::Renderable>(mainMenu, Ivy::Renderable("level-menu.png"));

		// Global variable to keep track of the score through AngelScript
		int r = Ivy::ScriptManager::GetInstance().getScriptEngine()->RegisterGlobalProperty("int level_score", &level_score); assert(r >= 0);
	}

	void update(Ivy::Timestep ts) override
	{
		if (isLoaded)
		{
			if (!isStarted) 
			{
				// Pause the game and show the menu on start
				Ivy::Application::GetInstance().isPaused = true;
				if (!loadedMenu)
				{
					Ivy::ECS::getInstance().addComponent<Ivy::Transform>(mainMenu, Ivy::Transform(Ivy::Application::GetCamera().position, 0.0f, menuSize));
					loadedMenu = true;
				}

				// Close the application and clear the ECS
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_X))
				{
					Ivy::ECS::getInstance().clearECS();
					Ivy::ScriptManager::GetInstance().garbageCollect(2);
					Ivy::Application::GetInstance().isRunning = false;
				}

				// Close the menu and start the game
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_SPACE))
				{
					Ivy::ECS::getInstance().removeComponent<Ivy::Transform>(mainMenu);
					isStarted = true;
					Ivy::Application::GetInstance().isPaused = false;
					loadedMenu = false;
				}
			}


			// Pause the game
			if (Ivy::InputHandler::IsKeyDown(IVY_KEY_P) && isStarted)
			{
				Ivy::Application::GetInstance().isPaused = true;
			}
			if (Ivy::Application::GetInstance().isPaused)
			{
				// Show the Menu
				if (!loadedMenu)
				{
					Ivy::ECS::getInstance().addComponent<Ivy::Transform>(mainMenu, Ivy::Transform(Ivy::Application::GetCamera().position, 0.0f, menuSize));
					loadedMenu = true;
				}

				// Close the application and clear the ECS
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_X))
				{
					Ivy::ECS::getInstance().clearECS();
					Ivy::ScriptManager::GetInstance().garbageCollect(2);		
					Ivy::Application::GetInstance().isRunning = false;
				}

				// Close the menu and restart the game
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_SPACE))
				{
					Ivy::ECS::getInstance().removeComponent<Ivy::Transform>(mainMenu);
					Ivy::Application::GetInstance().isPaused = false;
					loadedMenu = false;
				}

				// Restart the game
				if (Ivy::InputHandler::IsKeyDown(IVY_KEY_R))
				{
					isStarted = false; isLoaded = false; loadedMenu = false;
					Ivy::ECS::getInstance().clearECS();
					Ivy::CollisionSystem::refresh();
					Ivy::ScriptManager::GetInstance().garbageCollect(2);
					level_score = 0;
					mainMenu = Ivy::ECS::getInstance().createEntity();
					Ivy::ECS::getInstance().addComponent<Ivy::Renderable>(mainMenu, Ivy::Renderable("level-menu.png"));
				}
			}
		}
		else
		{
			Ivy::Application::GetInstance().isPaused = true;
			Ivy::Application::GetLevelGenerator().run();
			isLoaded = true;
		}

		// Check if the player won the level and generate a new one
		if (level_score == final_score)
		{
			isStarted = false; isLoaded = false; loadedMenu = false;
			Ivy::ECS::getInstance().clearECS();
			Ivy::CollisionSystem::refresh();
			Ivy::ScriptManager::GetInstance().garbageCollect(2);
			level_score = 0;
			mainMenu = Ivy::ECS::getInstance().createEntity();
			Ivy::ECS::getInstance().addComponent<Ivy::Renderable>(mainMenu, Ivy::Renderable("level-menu.png"));
		}

		Ivy::ScriptManager::GetInstance().garbageCollect(1);
	}

	void imGuiRender() override {}

	void onEvent(Ivy::Event& event) override {}

	~GameLayer() {}
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