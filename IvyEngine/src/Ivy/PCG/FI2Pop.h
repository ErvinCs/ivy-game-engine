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

		float mutationRate;	//0.05f
		float uniformRate;	//0.5f
		int singlePointCrossoverFrequency;	//3
		int eliteCount;	//2
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
		void clearPopulations();
		inline const Population& getFeasiblePopulation() { return feasiblePop; }
		inline const Population& getInfeasiblePopulation() { return infeasiblePop; }
		inline const Individual& getFittestFeasibleIndividual() { return fittestFeasible; }
		inline const Individual getFittestInfeasibleIndividual() { return fittestInfeasible; }

		Population evolvePopulation(const Population& pop);
		Population generateInitialPopulation();
		Individual generateRandomIndividual();

		Individual uniformCrossover(const Individual& ind1, const Individual& ind2);
		Individual singlePointCrossover(const Individual& ind1, const Individual& ind2);
		Individual tournamentSelection(const Population& pop);
		void mutate(Individual& ind);

		float computeFitness();
	private:
		void mutateRotation(DesignElement& designElement);
		void mutateLevelElement(LevelElement& levelElement, int geneIndex);

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