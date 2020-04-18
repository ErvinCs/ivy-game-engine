#include "ivypch.h"
#include "FI2Pop.h"

#include "DesignElements/LevelElement.h"
#include "../ECS/JSONManager.h"

namespace Ivy 
{
	FI2Pop::FI2Pop()
	{
		mutationRate = 0.05f;
		uniformRate = 0.5f;
		singlePointCrossoverFrequency = 3;
		eliteCount = 2;
		populationSize = 50;
		tournamentSize = 8;	    //???
		maxGeneration = 20;		//???
		genotypeSize = 10;
		targetFeasibleSize = 5;	    //???

		maxNodes = 144;
		minNodes = 0;

		init();
	}

	void FI2Pop::init()
	{
		feasiblePop = Population();
		infeasiblePop = Population();

		fittestFeasibleIndividual = Individual();
		fittestInfeasibleIndividual = Individual();

		fittestFeasibleFitness = 0.0f;
		fittestInfeasibleFitness = 0.0f;

		initialisedFeasible = false;
		initialisedInfeasible = false;
		currGeneration = 1;
		currentFeasibleSize = 0;	//???
		connectedComponents = 0;	//???

		generateInitialPopulation();
	}

	void FI2Pop::run()
	{
		while (currGeneration < maxGeneration || currentFeasibleSize < targetFeasibleSize)
		{
			if (initialisedInfeasible && (initialisedFeasible || feasiblePop.getPopulationSize() == 0))
			{
				while (infeasiblePop.getPopulationSize() > populationSize)
				{
					infeasiblePop.removeIndividualAtIndex(infeasiblePop.getLeastFitIndividualIndex());
				}

				feasiblePop.removeDeadIndividuals();

				currGeneration += 1;
				feasiblePop = this->evolvePopulation(feasiblePop);
				infeasiblePop = this->evolvePopulation(infeasiblePop);
				
			}
		}
		// First: on finding pop load into the ECS
		// Afterwards: On finding pop, write to JSON
	}

	Population FI2Pop::evolvePopulation(const Population & pop)
	{
		Population population = Population();
		
		if (pop.getPopulationSize() != 0)
		{
			int i = 0;
			while(i < eliteCount)
				population.addIndividual(pop.getFittestIndividual());
		}

		// Crossover
		for (int i = eliteCount; i < pop.getPopulationSize())
		{
			Individual ind1 = this->tournamentSelection(pop);
			Individual ind2 = this->tournamentSelection(pop);
			Individual offspring = Individual();
			if (singlePointCrossoverFrequency % 3 == 0)
				offspring = uniformCrossover(ind1, ind2);
			else
				offspring = singlePointCrossover(ind1, ind2);
			population.addIndividual(offspring);
		}

		// Mutation
		// Mutate one elite
		population.getIndividuals[eliteCount - 1];
		this->mutate(population.getIndividuals()[eliteCount-1]);
		for (int i = eliteCount; i < pop.getPopulationSize(); i++)
		{
			float randomUnit = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if (randomUnit <= mutationRate)
				this->mutate(population.getIndividuals()[i]);
		}

		return population;
	}

	Population FI2Pop::generateInitialPopulation()
	{
		Population randomPop = Population();
		for (int i = 0; i < populationSize; i++)
		{
			randomPop.addIndividual(this->generateRandomIndividual());
		}
		return randomPop;
	}

	Individual FI2Pop::generateRandomIndividual()
	{
		Individual individual{};
		
		for (int i = 0; i < genotypeSize; i++)
		{
			int randomRotationQuadrant = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 5));
			float rotation = randomRotationQuadrant * 90.0f;
			int roomType;
			// Do not allow traps at level beginning and end
			if (i == 0 || i == genotypeSize - 1)
				roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / LevelElement::ElementTypeCount - LevelElement::HostileTypeCount));
			else
				roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / LevelElement::ElementTypeCount));
			LevelElement piece = LevelElement(Tag("LevelElement" + LevelElement::TagCounter++), Transform(glm::vec2(1.0f), rotation, glm::vec2(1.0f)));
			piece.setElementType((ElementType)roomType);
			individual.addDesignElement(piece);
		}

		return individual;
	}

	// Copy rate of each
	Individual FI2Pop::uniformCrossover(const Individual & ind1, const Individual & ind2)
	{
		Individual offspring{};
		for (int i = 0; i < ind1.getDesignElements().size(); i++)
		{
			float copyDesignElemProb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if (ind1.getFitness() > ind2.getFitness())
			{
				if (copyDesignElemProb <= uniformRate)
				{
					offspring.addDesignElement(ind1.getDesignElements()[i]);
				}
				else
				{
					offspring.addDesignElement(ind2.getDesignElements()[i]);
				}
			}
			else
			{
				if (copyDesignElemProb <= uniformRate)
				{
					offspring.addDesignElement(ind2.getDesignElements()[i]);
				}
				else
				{
					offspring.addDesignElement(ind1.getDesignElements()[i]);
				}
			}
		}
		return offspring;
	}

	// CopyHalf of each
	Individual FI2Pop::singlePointCrossover(const Individual & ind1, const Individual & ind2)
	{
		Individual offspring{};
		int midPoint = genotypeSize / 2;
		float copyDesignElemProb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		for (int i = 0; i < ind1.getDesignElements().size(); i++)
		{
			if (copyDesignElemProb <= uniformRate)
			{
				// Copies half of individual 1 and half of individual 2
				if (i <= midPoint)
				{
					offspring.addDesignElement(ind1.getDesignElements()[i]);
				}
				else
				{
					offspring.addDesignElement(ind2.getDesignElements()[i]);
				}
			}
			else
			{
				// Copies half of individual 1 and half of individual 2
				if (i <= midPoint)
				{
					offspring.addDesignElement(ind2.getDesignElements()[i]);
				}
				else
				{
					offspring.addDesignElement(ind1.getDesignElements()[i]);
				}
			}
		}
		return offspring;
	}
	Individual FI2Pop::tournamentSelection(const Population & pop)
	{
		Population tournamentPop{};

		for (int i = 0; i < tournamentSize; i++)
		{
			int randIndex = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / pop.getPopulationSize()));
			tournamentPop.addIndividual(pop.getIndividuals()[i]);
		}

		return tournamentPop.getFittestIndividual();
	}

	void FI2Pop::mutate(Individual & ind)
	{
		for (int i = 0; i < ind.getDesignElements().size(); i++)
		{
			int mutationType = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 2));
			if (mutationType == 0)
			{
				this->mutateRotation(ind.getDesignElements()[i]);
			}
			else if (mutationType == 1)
			{
				this->mutateLevelElement((LevelPiece)ind.getDesignElements()[i], i);
			}

		}
	}

	void FI2Pop::mutateRotation(DesignElement& designElement)
	{
		float rotation = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 4));
		while (rotation * 90.0f == designElement.transform.rotation)
		{
			rotation = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 4));
		}
		rotation *= 90.0f;
		designElement.transform.rotation = rotation;
	}

	void FI2Pop::mutateLevelElement(LevelElement& levelElement, int geneIndex)
	{
		// Select random room type
		int roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / LevelElement::ElementTypeCount));
		// Keep changing piece until it's different
		while ((ElementType)roomType == levelElement.getElementType())
		{
			roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / LevelElement::ElementTypeCount));
		}
		// Do not allow traps at level beginning and end
		if (geneIndex == 0 || geneIndex == genotypeSize - 1)
			roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / LevelElement::ElementTypeCount - LevelElement::HostileTypeCount));

		levelElement.setElementType((ElementType)roomType); 
	}

	float FI2Pop::computeFitness()
	{
		// Normalize path costs
		float maxPathCost = (genotypeSize - 1) * maxNodes;
		float minPathCost = ((genotypeSize / 2) - 1) * minNodes;
		float normalizedShortestPathCost = (LevelGenerator.shortestPathCost - minPathCost) / (maxPathCost - minPathCost);

		// Normalize connected components
		float maxConnectedComponents = genotypeSize - 1;
		float minConnectedComponents = 0;
		float connectedComponentsScore = genotypeSize - connectedComponents;
		float normalizedConnectedComponentsScore = (connectedComponentsScore - minConnectedComponents) / (maxConnectedComponents - minConnectedComponents);

		return (float)(normalizedShortestPathCost + normalizedConnectedComponentsScore) / 3.0f;
	}
}