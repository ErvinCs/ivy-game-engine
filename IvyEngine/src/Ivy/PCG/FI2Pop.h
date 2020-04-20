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
		int shortestPathCost;

		int maxNodes;
		int minNodes;

		Graph* graph;
	public:
		FI2Pop() = default;
		FI2Pop(Graph* graph);

		void init();
		void run();

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
		void mutateRotation(DesignElement& designElement);
		void mutateLevelElement(DesignElement& levelElement, int geneIndex);

		inline float computeKConnectivityFitness()
		{
			int k = this->graph->getKConnectivity();
			return k / (genotypeSize * 2);
		}

		inline float computeVariableConnectivityFitness()
		{
			int k = this->graph->getVariableKConnectivity();
			return k / (genotypeSize * 4);
		}

		inline float computeConstraintFitness()
		{
			return (genotypeSize - connectedComponents) / (genotypeSize - 1);
		}

		inline float computePathFitness()
		{
			float minPathCost = (genotypeSize - 1) * maxNodes;
			float maxPathCost = 0;
			if (maxPathCost - minPathCost == 0)
				return 0;
			else
				return (shortestPathCost - minPathCost) / (maxPathCost - minPathCost);
		}

		inline float computeObjectiveFitness()
		{
			float pathFitness = computePathFitness();
			float kScore = computeKConnectivityFitness();
			return ((float)(pathFitness + kScore)) / 2.0f;
		}

	};

}