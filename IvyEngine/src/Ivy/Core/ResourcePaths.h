#pragma once

#include <filesystem>

namespace Paths {
	// Path to entities.json. Holds the data for all the entities and their associated components
	static const std::filesystem::path entitiesRepoPath = std::filesystem::absolute(std::filesystem::current_path() / "res" / "entities.json");
	// Path to the base shader provided by IvyEngine
	static const std::filesystem::path shaderPath = std::filesystem::absolute(std::filesystem::current_path() / ".." / "IvyEngine" / "res" / "shaders" / "base.glsl");
	// Path to the texture used by shaders in the absence of specification of other textures
	static const std::filesystem::path baseTexturePath = std::filesystem::absolute(std::filesystem::current_path() / ".." / "IvyEngine" / "res" / "textures" / "blank.png");
	// Path to the texture used by collidables to display their area
	static const std::filesystem::path collidablePath = std::filesystem::absolute(std::filesystem::current_path() / ".." / "IvyEngine" / "res" / "textures" / "coll.png");
	// Path to the directory of texture resources
	static const std::filesystem::path texturesPath = std::filesystem::absolute(std::filesystem::current_path() / "res" / "textures" / "");
	// Path to the directory of AngelScript script resources
	static const std::filesystem::path scriptsPath = std::filesystem::absolute(std::filesystem::current_path() / "res" / "scripts" / "");
}