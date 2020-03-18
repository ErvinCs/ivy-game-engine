#pragma once

#include "System.h"

#include <iostream>
#include <set>

namespace Ivy {

	class ScriptSystem : public System
	{
	public:
		ScriptSystem() = default;
		ScriptSystem(const std::vector<Entity>& entities)
		{
			this->setEntities(entities);
		}

		virtual void init() override;
		virtual void update(float deltatime) override;
	};

}
