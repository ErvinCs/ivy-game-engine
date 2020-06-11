#pragma once

#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES

#include "Population.h"
#include "Individual.h"
#include "DesignElement.h"
#include "Graph.h"


namespace Ivy 
{

	/**
	 * The Feasible-Infeasible Two-Populations Genetic Algorithm.
	 * Maintains a population of feasible individuals that satisfy all constraints and a 
	 *  population of infeasible individuals that do not.
	 * The constraints that must be satisifed is that a level should be traversable.
	 * This is determined by the type and rotation of each room where a room is a DesignElement.
	 * Feasible Individuals are evolved through Novelty Search.
	 * Infeasible Individuals are evolved to meet the mentioned constraint.
	 * @see DesignElement
	 * @see Individual
	 * @see Population
	 */
	class FI2Pop
	{
	private:
		Population feasiblePop;
		Population infeasiblePop;

		// The most fit feasible individual found across all runs of the algorithm
		Individual fittestFeasibleIndividual;
		float fittestFeasibleFitness;

		// The least fit feaisble individual found across all runs of the algorithm
		Individual leastFitFeasibleIndividual;
		float leastFitFeasibleFitness;

		// The most fit infeasible individual found across all runs of the algorithm
		Individual fittestInfeasibleIndividual;
		float fittestInfeasibleFitness;
		
		// True if at least 1 feasible individual has been found and false otherwise
		bool initialisedFeasible;
		// The size of the feasible population in the current generation
		int currentFeasibleSize;
		// The current generation
		int currGeneration;
		
	public:
		// Value in [0,1]
		static float mutationRate;
		// Value in [0,1]
		static float uniformRate;
		// Value in [0,1]
		static int singlePointCrossoverFrequency;
		// Number of individuals to not be affected by mutations
		static int eliteCount;
		// The generation at which the algorithm should stop running
		static int maxGeneration;

		static int populationSize;
		static int tournamentSize;
		static int genotypeSize;

		/**
		 * Initializes the population. Calls `init`.
		 */
		FI2Pop();

		/**
		 * Initalize most fit and least fit Individuals and their indices.
		 * Set the current generation and geenrate an initial population
		 */
		void init();

		/**
		 * Evolve the infeasible population.
		 * Evolve the feasible population if it exists.
		 * Migrations between populations occur if a feasible individual becomes infeasible and vice-versa
		 * Eliminate the least fit individual in any population that exceeds the population size threshold.
		 */
		void run();

		inline const Population& getFeasiblePopulation() { return feasiblePop; }
		inline const Population& getInfeasiblePopulation() { return infeasiblePop; }
		inline void setFittestFeasibleIndividual(const Individual& other) { this->fittestFeasibleIndividual = other; }
		inline void setFittestInfeasibleFeasibleIndividual(const Individual& other) { this->fittestInfeasibleIndividual = other; }
		inline void setLeastFitFeasibleIndividual(const Individual& other) { this->leastFitFeasibleIndividual = other; }
		inline const Individual& getFittestFeasibleIndividual() { return fittestFeasibleIndividual; }
		inline const Individual& getFittestInfeasibleIndividual() { return fittestInfeasibleIndividual; }
		inline const Individual& getLeastFitFeasibleIndividual() { return leastFitFeasibleIndividual; }
		inline const bool getInitialisedFeasible() { return this->initialisedFeasible; }

		/**
		 * Uses tournament selection to choose suitable individuals for reproduction.
		 * Uniform crossover is performed once every N individuals where N corresponds to the `singlePointCrossoverFrequency`.
		 * Single-point corssover is performed otherwise.
		 * Mutations are performed afterwards and can affect the rotation and ElementType.
		 * @param pop Population to be evolved
		 * @returns Population newly obtained after crossovers and mutations
		 */
		Population evolvePopulation(Population& pop);
		
		/**
		 * @returns Population an initial population formed of individuals generated randomly
		 */
		Population generateInitialPopulation();
		
		/**
		 * @returns Individual having random ElementTypes and random rotation
		 */
		Individual generateRandomIndividual();

		/**
		 * Performs uniform crossover on 2 individuals and returns their offspring 
		 * @param ind1 Individual
		 * @param ind2 Individual
		 * @returns Individual
		 */
		Individual uniformCrossover(Individual& ind1, Individual& ind2);
		
		/**
		 * Performs singlepoint crossover on 2 individuals and returns their offspring
		 * @param ind1 Individual
		 * @param ind2 Individual
		 * @returns Individual
		 */
		Individual singlePointCrossover(Individual& ind1, Individual& ind2);
		
		/**
		 * Performs a tournament with randomly chosen individuals.
		 * The tournament size is determined by the value of `tournamentSize`.
		 * @param pop Population to perform the tournament on
		 * @returns Individual with the highest fitness
		 */
		Individual tournamentSelection(Population& pop);
		
		/**
		 * Performs a mutation to the indviduals genes.
		 * The mutation can either change the ElementType of a gene or its rotation
		 */
		void mutate(Individual& ind);

		/**
		 * @returns Individual chosen randomly from the set of feasible individuals.
		 */
		Individual& getRandomFeasibleIndividual();

		/**
		 * Deletes all individuals in the feasible population.
		 */
		void clearFeasiblePop();

		/**
		 * Deletes all individuals in the infeasible population.
		 */
		void clearInfeasiblePop();
	private:

		/**
		 * Choose a new rotation for the given design element at random.
		 * @param designElement to be mutated
		 */
		void mutateRotation(DesignElement& designElement);
		
		/**
		 * Choose a new type for the ElementType of the given design element.
		 * @param designElement to be mutated
		 * @param geneIndex int representing an index in the gene collection such that starting/ending deisgn elements
		 *  arenote set to hostile types
		 */
		void mutateLevelElement(DesignElement& designElement, int geneIndex);
	};

}