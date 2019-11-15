#pragma once
#include "Manager.h"

namespace Ivy {

	class FileManager : public Manager
	{
	public:
		~FileManager() = default;

		static FileManager& getInstance()
		{
			static FileManager instance{};
			return instance;
		}
		

	protected:
		void initHook();
		void updateHook();
		void shutdownHook();

		FileManager() {}
		FileManager(const FileManager&) = delete;
		FileManager& operator=(const FileManager&) = delete;
	};

}