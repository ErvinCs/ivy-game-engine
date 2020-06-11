#pragma once

#include <vector>

#include "Individual.h"

namespace Ivy 
{
	/**
	 * A population of levels used by the PCG mechanism's GA.
	 * Maintains a collection of Individuals.
	 * @see Individual
	 */
	class Population
	{
	private:
		std::vector<Individual> individuals{};
	public:
		// Default Constructor
		Population() = default;

		/**
		 * Copy Constructor.
		 */
		Population(const Population& other);

		/**
		 * Constructs a population containing the given individuals
		 * @param individualList vector of Individuals
		 */
		Population(const std::vector<Individual>& individualList);

		/**
		 * @returns a modifiable copy of this population's individuals
		 */
		inline std::vector<Individual>& getIndividuals() { return this->individuals; }
		
		/**
		 * @returns a const copy of this population's individuals
		 */
		inline const std::vector<Individual>& getIndividualsConst() const { return this->individuals; }

		/**
		 * @returns Individual with the highest fitness in this population
		 */
		Individual getFittestIndividual();
		
		/**
		 * @returns Individual with the lowest fitness in this population
		 */
		Individual getLeastFitIndividual();
		
		/**
		 * @returns Individual with the highest diversity in this population
		 */
		Individual getMostFitAndDiverseIndividual();
		
		/**
		 * @returns in the index of the least fit individual
		 */
		int getLeastFitIndividualIndex();
		
		/**
		 * @returns int size of the population
		 */
		int getPopulationSize();
		
		/**
		 * Get an individual at a specified index
		 * @param index int representing the index in the collection of individuals
		 * @returns Individual at index
		 */
		Individual& getIndividualAt(int index);
		
		/**
		 * Internally sort the individuals based on fitness
		 */
		[[DEPRECATED]]
		void sortIndividuals();

		/**
		 * Add a new individual to this population
		 * @param Individual individual to be added to this population
		 */
		void addIndividual(const Individual& individual);

		/**
		 * Remove an individual from this population at a certain index.
		 * @param index int representing the index of the individual o be removed
		 */
		void removeIndividualAtIndex(int index);

		Population& Population::operator=(const Population& other);

		/**
		 * Computes the mean of the diversity values of all individuals in this population
		 * @returns float average diversity in the population
		 */
		const float feasibleAvgDiversity() const;

		/**
		 * Computes the mean of the fitness values of all individuals in this population
		 * @returns float average fitness in the population
		 */
		const float infeasibleAvgFitness() const;
	};
}