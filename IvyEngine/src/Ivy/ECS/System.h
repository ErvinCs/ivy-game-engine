#pragma once

#include <set>
#include "Entity.h"

namespace Ivy {

	class System
	{
	private:
		std::set<Entity*> entities;
	public:
		virtual void init() = 0;
		virtual void update(float deltatime) = 0;
	};


}