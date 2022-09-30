#include "ivypch.h"
#include "GenerationLayer.h"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "../PCG/LevelGenerator.h"
#include "../Core/Application.h"
#include "../ECS/ECS.h"
#include "../ECS/Systems/CollisionSystem.h"

namespace Ivy
{
	void GenerationLayer::imGuiRender()
	{
		// Create the Generator menu with the ID "Generation Layer"
		ImGui::Begin("Generator");
		ImGui::PushID("GenerationLayer");
		// Algorithm parameters
		if (ImGui::CollapsingHeader("Parameters"))
		{
			ImGui::InputFloat("Mutation Rate", &FI2Pop::MutationRate, 0.05f);
			ImGui::InputFloat("Uniform Rate", &FI2Pop::UniformRate, 0.5f);
			ImGui::InputInt("Elite Count", &FI2Pop::EliteCount, 1);
			ImGui::InputInt("Population Size", &FI2Pop::PopulationSize, 1);
			ImGui::InputInt("Tournament Size", &FI2Pop::TournamentSize, 1);
			ImGui::InputInt("Genotype Size", &FI2Pop::GenotypeSize, 1);
			ImGui::InputInt("Max Generation", &FI2Pop::MaxGeneration, 1);
			ImGui::Checkbox("Always Load", &LevelGenerator::AlwaysLoad);
			ImGui::RadioButton("Fittest", &LevelGenerator::AlwaysLoadFittest, 1);
			ImGui::RadioButton("Least Fit", &LevelGenerator::AlwaysLoadFittest, 0);
		}
		// Generation resources
		if (ImGui::CollapsingHeader("Resources"))
		{
			if (ImGui::TreeNode("Rooms"))
			{
				ImGui::InputText("Safe Room 1", &LevelGenerator::StdRoom1Path);	
				ImGui::InputText("Safe Room 2", &LevelGenerator::StdRoom2Path);
				ImGui::InputText("Dead End 1", &LevelGenerator::ClosedRoomPath);
				ImGui::InputText("Dead End 2", &LevelGenerator::MeleeEnemyPath);
				ImGui::InputText("Hallway", &LevelGenerator::HallwayPath);
				ImGui::InputText("T-Shaped Hallway", &LevelGenerator::TShapePath);
				ImGui::InputText("Middle Obstacle", &LevelGenerator::HolePath);
				ImGui::InputText("Pillar Room", &LevelGenerator::PillarPath);
				ImGui::InputText("Walls x4", &LevelGenerator::HorizontalWallPath);
				ImGui::InputText("Walls x3", &LevelGenerator::VerticalWallPath);
				ImGui::InputText("Walls x2", &LevelGenerator::RangedEnemyPath);	
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Player"))
			{
				ImGui::InputText("Player Sprite", &LevelGenerator::PlayerPath);
				ImGui::InputText("Player Script", &LevelGenerator::PlayerScript);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Enemies"))
			{
				ImGui::InputText("Enemy 1", &LevelGenerator::EnemyFlyPath);
				ImGui::InputText("Enemy 2", &LevelGenerator::EnemyGroundPath);
				ImGui::InputText("Enemy 1 Script", &LevelGenerator::ScriptPatrolH);
				ImGui::InputText("Enemy 2 Script", &LevelGenerator::ScriptPatrolV);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Items"))
			{
				ImGui::InputText("Item 1", &LevelGenerator::CollectablePath);
				ImGui::InputText("Item 1 Script", &LevelGenerator::CollectableScript);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Borders"))
			{
				ImGui::InputText("Horizontal Border", &LevelGenerator::HorizontalBorderPath);
				ImGui::InputText("Vertical Border", &LevelGenerator::VerticalBorderPath);
				ImGui::TreePop();
			}		
		}
		if (ImGui::Button("Run"))
		{
			Application::GetInstance().globalTime = 0.0f;
			Application::GetInstance().GetLevelGenerator().run();
			Application::GetInstance().lastFrameTime = (float)glfwGetTime();
		}
		if (ImGui::Button("Clear"))
		{
			Application::GetLevelGenerator().clearPopulations();
		}
		ImGui::PopID();
		ImGui::End();
	}
}