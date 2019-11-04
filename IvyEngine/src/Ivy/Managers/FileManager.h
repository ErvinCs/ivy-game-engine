#pragma once
#include "BaseManager.h"

namespace Ivy {

	class FileManager : public BaseManager
	{
	public:
		FileManager() {}
		~FileManager() {}

	protected:
		void initHook();
		void updateHook();
		void shutdownHook();


	};

}