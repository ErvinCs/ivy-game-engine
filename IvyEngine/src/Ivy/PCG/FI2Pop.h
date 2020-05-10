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

	class FI2Pop
	{
	private:
		Population feasiblePop;
		Population infeasiblePop;
		Individual fittestFeasibleIndividual;
		Individual leastFitFeasibleIndividual;
		Individual fittestInfeasibleIndividual;
		float fittestFeasibleFitness;
		float fittestInfeasibleFitness;
		float leastFitFeasibleFitness;
		bool initialisedFeasible;
		int currentFeasibleSize;
		int currGeneration;
		
	public:
		static float mutationRate;
		static float uniformRate;
		static int singlePointCrossoverFrequency;
		static int eliteCount;
		static int populationSize;
		static int tournamentSize;
		static int genotypeSize;
		static int maxGeneration;

		FI2Pop();

		void init();
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

		Population evolvePopulation(Population& pop);
		Population generateInitialPopulation();
		Individual generateRandomIndividual();

		Individual uniformCrossover(Individual& ind1, Individual& ind2);
		Individual singlePointCrossover(Individual& ind1, Individual& ind2);
		Individual tournamentSelection(Population& pop);
		void mutate(Individual& ind);

		Individual& getRandomFeasibleIndividual();

		void clearFeasiblePop();
		void clearInfeasiblePop();
	private:
		void mutateRotation(DesignElement& designElement);
		void mutateLevelElement(DesignElement& designElement, int geneIndex);
	};

}