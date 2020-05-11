#pragma once

#include <vector>

#include "Individual.h"

namespace Ivy 
{
	/*
	 *
	 */
	class Population
	{
	private:
		std::vector<Individual> individuals{};
	public:
		Population() = default;
		Population(const Population& other);
		Population(const std::vector<Individual>& individualList);

		inline std::vector<Individual>& getIndividuals() { return this->individuals; }
		inline const std::vector<Individual>& getIndividualsConst() const { return this->individuals; }

		Individual getFittestIndividual();
		Individual getLeastFitIndividual();
		Individual getMostFitAndDiverseIndividual();
		int getLeastFitIndividualIndex();
		int getPopulationSize();
		Individual& getIndividualAt(int index);
		
		void sortIndividuals();
		void addIndividual(const Individual& individual);
		void removeIndividualAtIndex(int index);

		Population& Population::operator=(const Population& other);
		const float feasibleAvgDiversity() const;
		const float infeasibleAvgFitness() const;
		// Has Issues
		//void removeDuplicates();
	};
}