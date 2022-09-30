#pragma once

#include "../json_nlohmann/json.hpp"
#include "Entity.h"

namespace Ivy {
	/**
	 * Static class that holds function pointer to convert entities
	 *  together with their associated components to and from JSON.
	 */
	class JSONManager
	{
	public:
		/**
		 * Vector of function pointers that point to conversion functions to JSON for all component types.
		 */
		static std::vector<std::function<void(Entity&, nlohmann::json&)>> SaveFunctions;

		/**
		 * Vector of function pointers that point to conversion functions from JSON for all component types.
		 */
		static std::vector<std::function<void(Entity&, nlohmann::json&)>> LoadFunctions;

		/**
		 * Initializes `SaveFunctions` and `LoadFunctions` with the component conversion function pointers
		 */
		static void InitFunctions();
		
		/**
		 * Loads all the entities and their associated components from JSON.
		 * @param path to the JSON file to load from
		 */
		static void LoadEntities(const std::string& path);
		
		/**
		 * Saves all entities and their associated components to JSON.
		 * @param path to the JSON file to load from
		 */
		static void SaveEntities(const std::string& path);
		
		/**
		 * Load the camera properties from JSON.
		 * @param path to the JSON file to load from
		 */
		static void LoadCamera(const std::string& path);
		
		/**
		 * Save the camera properties to JSON.
		 * @param path to the JSON file to save to
		 */
		static void SaveCamera(const std::string& path);

		/**
		 * Add a function pointer to `LoadFunctions`
		 * @see LoadFunctions
		 */
		static void AddLoadFunction(std::function<void(Entity&, nlohmann::json&)> func);

		/**
		 * Add a function pointer to `SaveFunctions`
		 * @see SaveFunctions
		 */
		static void AddSaveFunction(std::function<void(Entity&, nlohmann::json&)> func);
	}; 
}