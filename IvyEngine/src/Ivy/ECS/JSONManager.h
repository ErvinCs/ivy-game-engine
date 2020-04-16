#pragma once

#include "../json_nlohmann/json.hpp"
#include "Entity.h"

namespace Ivy {

	class JSONManager
	{
	public:
		//using ConvFunc = std::function<void(Entity&, nlohmann::json&)>;
		//using Json = nlohmann::json;
		static std::vector<std::function<void(Entity&, nlohmann::json&)>> SaveFunctions;
		static std::vector<std::function<void(Entity&, nlohmann::json&)>> LoadFunctions;

		static void InitFunctions();
		static void LoadEntities(const std::string& path);
		static void SaveEntities(const std::string& path);
		static void LoadCamera(const std::string& path);
		static void SaveCamera(const std::string& path);

		static void addLoadFunction(std::function<void(Entity&, nlohmann::json&)> func);
		static void addSaveFunction(std::function<void(Entity&, nlohmann::json&)> func);
	}; 
}