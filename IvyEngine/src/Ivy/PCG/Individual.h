#pragma once

#include <vector>
#include "DesignElement.h"


namespace Ivy {
	class Individual
	{
	private:
		std::vector<DesignElement*> designElements{};
		float fitness;
		bool alive;
	public:
		Individual();
		Individual(const Individual& other);
		Individual(const std::vector<DesignElement*>& designElements);

		inline std::vector<DesignElement*>& getDesignElements() { return designElements; }
		inline const float& getFitness() const { return fitness; }
		inline const bool& isAlive() { return alive; }
		inline void setDesignElements(const std::vector<DesignElement*>& designElements) { this->designElements = designElements; }
		inline void setFitness(const float& fitness) { this->fitness = fitness; }
		inline void setAlive(const bool& alive) { this->alive = alive; }

		void sortDesignElements();
		float getDiversityFactor(Individual& other);
		float getLinearityFactor();
		void addDesignElement(DesignElement* designElement) { designElements.push_back(designElement); }

		/*
		 * Two individuals are equal if all their design elements are equal.
		 * Returns true if two individuals are equal and false otherwise
		 */
		bool operator==(Individual& other);
		bool operator!=(Individual& other);
		
	};
}