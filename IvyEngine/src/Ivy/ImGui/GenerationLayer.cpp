#include "ivypch.h"
#include "GenerationLayer.h"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "../PCG/LevelGenerator.h"
#include "../Core/Application.h"
#include "../ECS/ECS.h"

namespace Ivy
{
	void GenerationLayer::imGuiRender()
	{
		ImGui::Begin("Generator");
		ImGui::PushID("GenerationLayer");
		if (ImGui::CollapsingHeader("Parameters"))
		{
			ImGui::InputFloat("Mutation Rate", &FI2Pop::mutationRate, 0.05f);
			ImGui::InputFloat("Uniform Rate", &FI2Pop::uniformRate, 0.5f);
			ImGui::InputInt("Elite Count", &FI2Pop::eliteCount, 1);
			ImGui::InputInt("Population Size", &FI2Pop::populationSize, 1);
			ImGui::InputInt("Tournament Size", &FI2Pop::tournamentSize, 1);
			ImGui::InputInt("Genotype Size", &FI2Pop::genotypeSize, 1);
			ImGui::InputInt("Max Generation", &FI2Pop::maxGeneration, 1);
			ImGui::Checkbox("Always Load", &LevelGenerator::alwaysLoad);
			ImGui::RadioButton("Fittest", &LevelGenerator::alwaysLoadFittest, 1);
			ImGui::RadioButton("Least Fit", &LevelGenerator::alwaysLoadFittest, 0);
		}
		if (ImGui::CollapsingHeader("Resources"))
		{
			if (ImGui::TreeNode("Rooms"))
			{
				ImGui::InputText("Safe Room 1", &LevelGenerator::stdRoom1Path);	
				ImGui::InputText("Safe Room 2", &LevelGenerator::stdRoom2Path);
				ImGui::InputText("Dead End 1", &LevelGenerator::closedRoomPath);
				ImGui::InputText("Dead End 2", &LevelGenerator::meleeEnemyPath);
				ImGui::InputText("Hallway", &LevelGenerator::hallwayPath);
				ImGui::InputText("T-Shaped Hallway", &LevelGenerator::tShapePath);
				ImGui::InputText("Middle Obstacle", &LevelGenerator::holePath);
				ImGui::InputText("Half-Enclosed Middle Obstacle", &LevelGenerator::pillarPath);
				ImGui::InputText("Walls x4", &LevelGenerator::horizontalWallPath);
				ImGui::InputText("Walls x3", &LevelGenerator::verticalWallPath);
				ImGui::InputText("Walls x2", &LevelGenerator::rangedEnemyPath);	
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Player"))
			{
				ImGui::InputText("Player Sprite", &LevelGenerator::playerPath);
				ImGui::InputText("Player Script", &LevelGenerator::playerScript);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Enemy Sprites"))
			{
				ImGui::InputText("Flying Enemy", &LevelGenerator::enemyFlyPath);
				ImGui::InputText("Ground Enemy", &LevelGenerator::enemyGroundPath);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Enemy Scripts"))
			{
				ImGui::InputText("Enemy Script 1", &LevelGenerator::scriptPatrolH);
				ImGui::InputText("Enemy Script 2", &LevelGenerator::scriptPatrolV);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Borders"))
			{
				ImGui::InputText("Horizontal Border", &LevelGenerator::horizontalBorderPath);
				ImGui::InputText("Vertical Border", &LevelGenerator::verticalBorderPath);
				ImGui::TreePop();
			}		
		}
		if (ImGui::Button("Run"))
		{
			Application::getInstance().globalTime = 0.0f;
			Application::getInstance().GetLevelGenerator().run();
			Application::getInstance().lastFrameTime = (float)glfwGetTime();
		}
		ImGui::PopID();
		ImGui::End();
	}
}