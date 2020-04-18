#pragma once

#include <stdlib.h>

#include "Population.h"
#include "Individual.h"
#include "DesignElements/LevelElement.h"

namespace Ivy 
{

	class FI2Pop
	{
	private:
		Population feasiblePop;
		Population infeasiblePop;
		Individual fittestFeasibleIndividual;
		Individual fittestInfeasibleIndividual;
		float fittestFeasibleFitness;
		float fittestInfeasibleFitness;
		bool initialisedFeasible;
		bool initialisedInfeasible;

		float mutationRate;
		float uniformRate;	
		int singlePointCrossoverFrequency;	
		int eliteCount;
		int populationSize;
		int tournamentSize;
		int maxGeneration;
		int currGeneration;
		int genotypeSize;
		int targetFeasibleSize;
		int currentFeasibleSize;
		int connectedComponents;

		int maxNodes;
		int minNodes;
	public:
		FI2Pop();

		void init();
		void run();
		//void clearPopulations();
		inline const Population& getFeasiblePopulation() { return feasiblePop; }
		inline const Population& getInfeasiblePopulation() { return infeasiblePop; }
		inline const Individual& getFittestFeasibleIndividual() { return fittestFeasibleIndividual; }
		inline const Individual getFittestInfeasibleIndividual() { return fittestInfeasibleIndividual; }

		Population evolvePopulation(Population& pop);
		Population generateInitialPopulation();
		Individual generateRandomIndividual();

		Individual uniformCrossover(Individual& ind1, Individual& ind2);
		Individual singlePointCrossover(Individual& ind1, Individual& ind2);
		Individual tournamentSelection(Population& pop);
		void mutate(Individual& ind);

		float computeFitness();
	private:
		void mutateRotation(DesignElement* designElement);
		void mutateLevelElement(LevelElement* levelElement, int geneIndex);

		inline float computeKConnectivityFitness()
		{

		}

		inline float computeConnectivityFitness()
		{

		}

		inline float computeConstraintFitness()
		{

		}

		inline float computePathFitness()
		{

		}

		inline float computeObjectiveFitness()
		{

		}

	};

}