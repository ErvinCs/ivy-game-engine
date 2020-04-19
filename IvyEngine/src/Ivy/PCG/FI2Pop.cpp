#include "ivypch.h"
#include "FI2Pop.h"

#include "DesignElements/LevelElement.h"
#include "../Core/Logger.h"

namespace Ivy 
{
	FI2Pop::FI2Pop(Graph* graph)
	{
		mutationRate = 0.05f;
		uniformRate = 0.5f;
		singlePointCrossoverFrequency = 3;
		eliteCount = 2;
		populationSize = 50;
		tournamentSize = 8;	    //???
		maxGeneration = 20;		//???
		genotypeSize = 12;
		targetFeasibleSize = 5;	    //???
		shortestPathCost = 0;

		maxNodes = 144;
		minNodes = 0;

		init();
		this->graph = graph;
	}

	void FI2Pop::init()
	{
		fittestFeasibleIndividual = Individual();
		fittestInfeasibleIndividual = Individual();

		fittestFeasibleFitness = 0.0f;
		fittestInfeasibleFitness = 0.0f;

		initialisedFeasible = false;
		initialisedInfeasible = true;
		currGeneration = 1;
		currentFeasibleSize = 0;	//???
		connectedComponents = 0;	//???

		feasiblePop = Population();
		infeasiblePop = generateInitialPopulation();
	}

	void FI2Pop::run()
	{
		IVY_CORE_TRACE("FI2POP: Starting run");
		while (currGeneration < maxGeneration)	// || currentFeasibleSize < targetFeasibleSize
		{
			IVY_CORE_TRACE("FI2POP: Generation {0}", currGeneration);
			if (initialisedInfeasible && (initialisedFeasible || feasiblePop.getPopulationSize() == 0))
			{
				while (infeasiblePop.getPopulationSize() > populationSize)
				{
					IVY_CORE_TRACE("FI2POP: Removing extra individual at index {0}. Size of Infeasible: {1}", infeasiblePop.getLeastFitIndividualIndex(), infeasiblePop.getPopulationSize());
					infeasiblePop.removeIndividualAtIndex(infeasiblePop.getLeastFitIndividualIndex());
				}

				feasiblePop.removeDeadIndividuals();

				currGeneration += 1;
				IVY_CORE_TRACE("FI2POP: Evolving Infeasible");
				infeasiblePop = this->evolvePopulation(infeasiblePop);
				if (initialisedFeasible)
				{
					IVY_CORE_TRACE("FI2POP: Evolving Infeasible");
					feasiblePop = this->evolvePopulation(feasiblePop);
				}
				
			}
		}
		// First: on finding pop load into the ECS
		// Afterwards: On finding pop, write to JSON
	}

	Population FI2Pop::evolvePopulation(Population& pop)
	{
		//IVY_CORE_TRACE("FI2POP: Evolving Population. Size={0}", pop.getPopulationSize());
		Population population = Population();
		
		if (pop.getPopulationSize() != 0)
		{
			int i = 0;
			while (i < eliteCount)
			{
				//IVY_CORE_TRACE("FI2POP: Adding elite {0}", i);
				population.addIndividual(pop.getFittestIndividual());
				i++;
			}
		}

		//IVY_CORE_TRACE("FI2POP: Starting Crossover");
		// Crossover
		for (int i = eliteCount; i < pop.getPopulationSize(); i++)
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
		//IVY_CORE_TRACE("FI2POP: Ending Crossover");

		// Mutation
		// Mutate one elite
		//IVY_CORE_TRACE("FI2POP: Starting Mutation");
		this->mutate(population.getIndividuals()[eliteCount-1]);
		for (int i = eliteCount; i < pop.getPopulationSize(); i++)
		{
			float randomUnit = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if (randomUnit <= mutationRate)
				this->mutate(population.getIndividuals()[i]);
		}
		//IVY_CORE_TRACE("FI2POP: Ending Mutation");

		return population;
	}

	Population FI2Pop::generateInitialPopulation()
	{
		// Generating Initial Population
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
			int randomRotationQuadrant = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 4));
			float rotation;
			switch (randomRotationQuadrant)
			{
			case 0:
				rotation = 0;
				break;
			case 1:
				rotation = M_PI_2;
				break;
			case 2:
				rotation = M_PI_2;
				break;
			case 3:
				rotation = 3.0f * M_PI_2;
				break;
			default:
				rotation = 0;
				break;
			}
			int roomType;
			const glm::vec2 roomSize = glm::vec2(8.0f, 8.0f);
			// Do not allow traps at level beginning and end
			if (i == 0 || i == genotypeSize - 1)
				roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / LevelElement::ElementTypeCount - LevelElement::HostileTypeCount));
			else
				roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / LevelElement::ElementTypeCount));
			Transform roomTransform;
			switch (roomType)
			{
			case ElementType::Hallway:
				roomTransform = Transform(glm::vec2(1.0f), rotation, roomSize);
				break;
			case ElementType::Hole:
				roomTransform = Transform(glm::vec2(1.0f), rotation, roomSize);
				break;
			case ElementType::HorizontalWall:
				roomTransform = Transform(glm::vec2(1.0f), rotation, roomSize);
				break;
			case ElementType::Pillar:
				roomTransform = Transform(glm::vec2(1.0f), rotation, roomSize);
				break;
			case ElementType::VerticalWall:
				roomTransform = Transform(glm::vec2(1.0f), rotation, roomSize);
				break;
			case ElementType::RangedEnemy:
				roomTransform = Transform(glm::vec2(1.0f), rotation, roomSize);
				break;
			}

			LevelElement* piece = new LevelElement(Tag(std::string("LevelElement" + LevelElement::TagCounter++)), roomTransform);
			piece->setElementType((ElementType)roomType);
			individual.addDesignElement(piece);
		}

		return individual;
	}

	// Copy rate of each
	Individual FI2Pop::uniformCrossover(Individual& ind1, Individual& ind2)
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
	Individual FI2Pop::singlePointCrossover(Individual& ind1, Individual& ind2)
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
	Individual FI2Pop::tournamentSelection(Population & pop)
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
				this->mutateLevelElement((LevelElement*)ind.getDesignElements()[i], i);
			}

		}
	}

	void FI2Pop::mutateRotation(DesignElement* designElement)
	{
		int randomRotationQuadrant = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 4));
		float rotation;
		switch (randomRotationQuadrant)
		{
		case 0:
			rotation = 0;
			break;
		case 1:
			rotation = M_PI_2;
			break;
		case 2:
			rotation = M_PI_2;
			break;
		case 3:
			rotation = 3.0f * M_PI_2;
			break;
		default:
			rotation = 0;
			break;
		}
		while (rotation == designElement->transform.rotation)
		{
			randomRotationQuadrant = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 4));
			switch (randomRotationQuadrant)
			{
			case 0:
				rotation = 0;
				break;
			case 1:
				rotation = M_PI_2;
				break;
			case 2:
				rotation = M_PI_2;
				break;
			case 3:
				rotation = 3.0f * M_PI_2;
				break;
			default:
				rotation = 0;
				break;
			}
		}
		designElement->transform.rotation = rotation;
	}

	void FI2Pop::mutateLevelElement(LevelElement* levelElement, int geneIndex)
	{
		// Select random room type
		int roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / LevelElement::ElementTypeCount));
		// Keep changing piece until it's different
		while ((ElementType)roomType == levelElement->getElementType())
		{
			roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / LevelElement::ElementTypeCount));
		}
		// Do not allow traps at level beginning and end
		if (geneIndex == 0 || geneIndex == genotypeSize - 1)
			roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / LevelElement::ElementTypeCount - LevelElement::HostileTypeCount));

		levelElement->setElementType((ElementType)roomType); 
	}

	float FI2Pop::computeFitness()
	{
		// Normalize path costs
		float maxPathCost = (genotypeSize - 1) * maxNodes;
		float normalizedShortestPathCost = shortestPathCost / maxPathCost;

		// Normalize connected components
		float maxConnectedComponents = genotypeSize - 1;
		float connectedComponentsScore = genotypeSize - connectedComponents;
		float normalizedConnectedComponentsScore = connectedComponentsScore / maxConnectedComponents;

		// Normalize K connectivity
		int kConnectivity = graph->getKConnectivity();
		float normalizedVertexConnectivity = (kConnectivity) / (genotypeSize * 2);

		return ((float)(normalizedShortestPathCost + normalizedConnectedComponentsScore + normalizedVertexConnectivity)) / 3.0f;
	}
}