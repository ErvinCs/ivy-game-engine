#pragma once

#include <filesystem>

namespace Paths {
	static const std::filesystem::path entitiesRepoPath = std::filesystem::absolute(std::filesystem::current_path() / "res" / "entities.json");
	static const std::filesystem::path shaderPath = std::filesystem::absolute(std::filesystem::current_path() / ".." / "IvyEngine" / "res" / "shaders" / "base.glsl");
	static const std::filesystem::path baseTexturePath = std::filesystem::absolute(std::filesystem::current_path() / ".." / "IvyEngine" / "res" / "textures" / "blank.png");
}