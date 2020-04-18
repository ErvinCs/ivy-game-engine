#pragma once

#include <vector>
#include "Individual.h"

namespace Ivy {
	class Population
	{
	private:
		std::vector<Individual> individuals{};
	public:
		Population() = default;
		Population(const Population& other);
		Population(const std::vector<Individual>& individualList);

		inline const std::vector<Individual>& getIndividuals() { return this->individuals; }

		Individual getFittestIndividual();
		Individual getLeastFitIndividual();
		int getLeastFitIndividualIndex();
		int getPopulationSize();

		void sortIndividuals();
		void addIndividual(const Individual& individual);
		void removeIndividual(const Individual& individual);
		void removeIndividualAtIndex(int index);
		void removeDeadIndividuals();
	};
}