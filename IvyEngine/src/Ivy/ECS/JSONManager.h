#pragma once

namespace Ivy {

	class JSONManager
	{
	private:
		//static std::vector<> ConversionFunctions
	public:
		static void LoadEntities(const std::string& path);
		static void SaveEntities(const std::string& path);
	};
}