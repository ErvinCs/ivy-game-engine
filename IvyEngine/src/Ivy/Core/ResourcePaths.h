#pragma once

#include <filesystem>

namespace Paths {
	// Path to entities.json. Holds the data for all the entities and their associated components
	static const std::filesystem::path ENTITIES_REPO_PATH = std::filesystem::absolute(std::filesystem::current_path() / "res" / "entities.json");
	// Path to the base shader provided by IvyEngine
	static const std::filesystem::path SHADER_PATH = std::filesystem::absolute(std::filesystem::current_path() / ".." / "IvyEngine" / "res" / "shaders" / "base.glsl");
	// Path to the texture used by shaders in the absence of specification of other textures
	static const std::filesystem::path BASE_TEXTURE_PATH = std::filesystem::absolute(std::filesystem::current_path() / ".." / "IvyEngine" / "res" / "textures" / "blank.png");
	// Path to the texture used by collidables to display their area
	static const std::filesystem::path COLLIDABLE_PATH = std::filesystem::absolute(std::filesystem::current_path() / ".." / "IvyEngine" / "res" / "textures" / "collBox.png");
	// Path to the directory of texture resources
	static const std::filesystem::path TEXTURES_PATH = std::filesystem::absolute(std::filesystem::current_path() / "res" / "textures" / "");
	// Path to the directory of AngelScript script resources
	static const std::filesystem::path SCRIPTS_PATH = std::filesystem::absolute(std::filesystem::current_path() / "res" / "scripts" / "");
	// Path to camera.json. Holds the data for the gloval orthographic camera 
	static const std::filesystem::path CAMERA_REPOSITORY_PATH = std::filesystem::absolute(std::filesystem::current_path() / "res" / "camera.json");
}