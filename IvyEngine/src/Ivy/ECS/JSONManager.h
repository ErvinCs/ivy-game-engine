#pragma once

namespace Ivy {

	class JSONManager
	{
	public:
		static void LoadEntities(const std::string& path);
		static void SaveEntities(const std::string& path);
	};

}