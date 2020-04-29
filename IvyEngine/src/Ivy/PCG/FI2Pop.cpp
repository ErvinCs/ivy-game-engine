#include "ivypch.h"
#include "FI2Pop.h"

#include "../Core/Logger.h"

namespace Ivy 
{
	float FI2Pop::mutationRate = 0.1f;
	float FI2Pop::uniformRate = 0.5f;
	int FI2Pop::singlePointCrossoverFrequency = 3;
	int FI2Pop::eliteCount = 2;
	int FI2Pop::populationSize = 26;
	int FI2Pop::tournamentSize = 6;
	int FI2Pop::genotypeSize = 12;
	int FI2Pop::maxGeneration = 5;

	FI2Pop::FI2Pop()
	{
		init();
	}

	void FI2Pop::init()
	{
		fittestFeasibleIndividual = Individual();
		fittestInfeasibleIndividual = Individual();
		leastFitFeasibleIndividual = Individual();

		fittestFeasibleFitness = 0.0f;
		fittestInfeasibleFitness = 0.0f;
		leastFitFeasibleFitness = 1.0f;

		initialisedFeasible = false;
		currGeneration = 1;
		currentFeasibleSize = 0;

		feasiblePop = Population();
		infeasiblePop = generateInitialPopulation();
	}

	void FI2Pop::run()
	{
		IVY_CORE_TRACE("FI2POP: Starting run");
		while (currGeneration <= maxGeneration)	
		{
			IVY_CORE_TRACE("FI2POP: Generation {0}", currGeneration);

			if (infeasiblePop.getPopulationSize() > populationSize)
			{
				while (infeasiblePop.getPopulationSize() > populationSize)
				{
					IVY_CORE_TRACE("FI2POP: Removing extra individual at index {0}. Size of Infeasible: {1}", infeasiblePop.getLeastFitIndividualIndex(), infeasiblePop.getPopulationSize());
					infeasiblePop.removeIndividualAtIndex(infeasiblePop.getLeastFitIndividualIndex());
				}
			}

			IVY_CORE_TRACE("FI2POP: Evolving Infeasible");
			infeasiblePop = this->evolvePopulation(infeasiblePop);
			if (initialisedFeasible)
			{
				IVY_CORE_TRACE("FI2POP: Evolving Feasible");
				feasiblePop = this->evolvePopulation(feasiblePop);
			}

			IVY_CORE_TRACE("FI2POP: Computing Infeasible Fitnesses");
			int infeasiblePopSize = infeasiblePop.getPopulationSize();
			int migrated = 0;
			for (int i = 0; i < infeasiblePopSize; i++)
			{
				Individual& ind = infeasiblePop.getIndividualAt(i);
				ind.computeFitness();
				if (ind.getFitness() == 1.0f)
				{
					IVY_CORE_TRACE("FI2POP: Migrating");
					feasiblePop.addIndividual(ind);
					infeasiblePop.removeIndividualAtIndex(i);
					infeasiblePopSize--;
					i--;
					initialisedFeasible = true;
				}
				else
				{
					float thisFitness = ind.getFitness();
					if (thisFitness > fittestInfeasibleFitness)
					{
						fittestInfeasibleFitness = thisFitness;
						this->setFittestInfeasibleFeasibleIndividual(infeasiblePop.getIndividualAt(i));

					}
				}
			}

			for (int i = infeasiblePop.getPopulationSize(); i < populationSize; i++)
			{
				IVY_CORE_TRACE("FI2POP: Repopulating with random infeasible {0}", i);
				infeasiblePop.addIndividual(this->generateRandomIndividual());
			}

			
			if (initialisedFeasible)
			{
				IVY_CORE_TRACE("FI2POP: Computing Feasible Fitnesses");
				int popSize = feasiblePop.getPopulationSize();
				float diversity = 0.0f;
				
				for (int i = 0; i < popSize; i++)
				{
					Individual& ind = feasiblePop.getIndividualAt(i);
					bool removed = false;
					float fitness = ind.computeFitness();
					diversity = 0;
					if (fitness < 1.0f)
					{
						infeasiblePop.addIndividual(ind);
						feasiblePop.removeIndividualAtIndex(i);
						popSize--;
						i--;
						continue;
					}
					if (popSize > 1)
					{
						for (int j = 0; j < popSize; j++)
						{
							if (i == j)
								continue;
							diversity += ind.computeDiversity(feasiblePop.getIndividualAt(j));
						}
						diversity /= (popSize - 1);
					}
					
					ind.setDiversity(diversity);
					ind.setFitness(diversity);
					if (diversity > fittestFeasibleFitness)
					{
						fittestFeasibleFitness = diversity;
						this->setFittestFeasibleIndividual(feasiblePop.getIndividualAt(i));
						IVY_CORE_TRACE("FI2POP: Top Feasible Individual. Has Diversity = {0}", diversity);
					}
					if (diversity < leastFitFeasibleFitness)
					{
						leastFitFeasibleFitness = diversity;
						this->setLeastFitFeasibleIndividual(feasiblePop.getIndividualAt(i));
						IVY_CORE_TRACE("FI2POP: Worst Feasible Individual. Has Diversity = {0}", diversity);
					}
				}
			}
			currGeneration += 1;
		}
		currGeneration = 1;
	}

	Population FI2Pop::evolvePopulation(Population& oldPop)
	{
		Population population = Population();
		
		if (oldPop.getPopulationSize() != 0)
		{
			int i = 0;
			while (i < eliteCount)
			{
				population.addIndividual(oldPop.getFittestIndividual());
				i++;
			}
		}

		// Crossover
		int oldPopSize = oldPop.getPopulationSize();
		if (oldPopSize >= eliteCount && oldPopSize >= tournamentSize)
		{
			for (int i = eliteCount; i < oldPopSize; i++)
			{
				Individual ind1 = this->tournamentSelection(oldPop);
				Individual ind2 = this->tournamentSelection(oldPop);
				Individual offspring = Individual();
				if (i % singlePointCrossoverFrequency == 0)
					offspring = uniformCrossover(ind1, ind2);
				else
					offspring = singlePointCrossover(ind1, ind2);
				population.addIndividual(offspring);
			}

			// Mutation
			// Mutate one elite
			this->mutate(population.getIndividualAt(eliteCount - 1));
			int currPopSize = population.getPopulationSize();
			for (int i = eliteCount; i < currPopSize; i++)
			{
				float randomUnit = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				if (randomUnit <= mutationRate)
				{
					this->mutate(population.getIndividualAt(i));
				}
			}
		}
		else if (oldPopSize != 0)
		{
			int randIndex;
			for (int i = eliteCount; i < oldPopSize; i++)
			{
				randIndex = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / oldPopSize));
				Individual ind1 = oldPop.getIndividualAt(randIndex);
				randIndex = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / oldPopSize));
				Individual ind2 = oldPop.getIndividualAt(randIndex);
				Individual offspring = Individual();
				if (i % singlePointCrossoverFrequency == 0)
					offspring = uniformCrossover(ind1, ind2);
				else
					offspring = singlePointCrossover(ind1, ind2);
				population.addIndividual(offspring);
			}


			// Mutation
			// Mutate one elite
			int currPopSize = population.getPopulationSize();
			this->mutate(population.getIndividualAt(eliteCount - 1));
			for (int i = eliteCount; i < currPopSize; i++)
			{
				float randomUnit = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				if (randomUnit <= mutationRate)
				{
					this->mutate(population.getIndividualAt(i));
				}
			}
		}
		
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
		
		int elemTypeCount = DesignElement::ElementTypeCount;
		int hostileTypeCount = DesignElement::HostileTypeCount ;
		for (int i = 0; i < genotypeSize; i++)
		{
			int randomRotationQuadrant = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 3));
			float rotation;
			switch (randomRotationQuadrant)
			{
			case 1:
				rotation = M_PI_2;
				break;
			case 2:
				rotation = M_PI;
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
				roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / (elemTypeCount - hostileTypeCount - 1)));
			else
				roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / (elemTypeCount - 1)));
			Transform roomTransform = Transform(glm::vec2(1.0f), rotation, roomSize);

			DesignElement piece = DesignElement(Tag(std::string("LevelElement" + std::to_string(DesignElement::TagCounter++))), roomTransform);
			piece.setElementType((ElementType)roomType);
			individual.addDesignElement(piece);
		}

		return individual;
	}

	Individual FI2Pop::uniformCrossover(Individual& ind1, Individual& ind2)
	{
		Individual offspring{};
		for (int i = 0; i < genotypeSize; i++)
		{
			float copyDesignElemProb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if (ind1.getFitness() > ind2.getFitness())
			{
				if (copyDesignElemProb <= uniformRate)
				{
					offspring.addDesignElement(ind1.getDesignElementAt(i));
				}
				else
				{
					offspring.addDesignElement(ind2.getDesignElementAt(i));
				}
			}
			else
			{
				if (copyDesignElemProb <= uniformRate)
				{
					offspring.addDesignElement(ind2.getDesignElementAt(i));
				}
				else
				{
					offspring.addDesignElement(ind1.getDesignElementAt(i));
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
		for (int i = 0; i < genotypeSize; i++)
		{
			if (copyDesignElemProb <= uniformRate)
			{
				// Copies half of individual 1 and half of individual 2
				if (i <= midPoint)
				{
					offspring.addDesignElement(ind1.getDesignElementAt(i));
				}
				else
				{
					offspring.addDesignElement(ind2.getDesignElementAt(i));
				}
			}
			else
			{
				// Copies half of individual 1 and half of individual 2
				if (i <= midPoint)
				{
					offspring.addDesignElement(ind2.getDesignElementAt(i));
				}
				else
				{
					offspring.addDesignElement(ind1.getDesignElementAt(i));
				}
			}
		}
		return offspring;
	}


	Individual FI2Pop::tournamentSelection(Population & pop)
	{
		int populationSize = pop.getPopulationSize() - 1;
		int randIndex = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / populationSize));
		Individual winner = pop.getIndividualAt(randIndex);

		Individual current;
		for (int i = 1; i < tournamentSize; i++)
		{
			randIndex = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / populationSize));
			current = pop.getIndividualAt(randIndex);
			
			if (current.getFitness() > winner.getFitness())
				winner = current;
		}

		return winner;
	}

	void FI2Pop::mutate(Individual & ind)
	{
		for (int i = 0; i < genotypeSize; i++)
		{
			int mutationType = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 2));
			if (mutationType == 0)
			{
				this->mutateRotation(ind.getDesignElementAt(i));
			}
			else
			{
				this->mutateLevelElement(ind.getDesignElementAt(i), i);
			}

		}
	}

	void FI2Pop::mutateRotation(DesignElement& designElement)
	{
		int randomRotationQuadrant = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 3));
		float rotation;
		switch (randomRotationQuadrant)
		{
		case 1:
			rotation = M_PI_2;
			break;
		case 2:
			rotation = M_PI;
			break;
		case 3:
			rotation = 3.0f * M_PI_2;
			break;
		default:
			rotation = 0;
			break;
		}
		while (rotation == designElement.transform.rotation)
		{
			randomRotationQuadrant = static_cast<int> (rand()) / (static_cast <float> (RAND_MAX / 3));
			switch (randomRotationQuadrant)
			{
			case 1:
				rotation = M_PI_2;
				break;
			case 2:
				rotation = M_PI;
				break;
			case 3:
				rotation = 3.0f * M_PI_2;
				break;
			default:
				rotation = 0;
				break;
			}
		}
		designElement.transform.rotation = rotation;
	}

	void FI2Pop::mutateLevelElement(DesignElement& designElement, int geneIndex)
	{
		// Select random room type
		int roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / (DesignElement::ElementTypeCount - 1)));
		// Keep changing piece until it's different
		while ((ElementType)roomType == designElement.getElementType())
		{
			roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / (DesignElement::ElementTypeCount - 1)));
		}
		// Do not allow traps at level beginning and end
		if (geneIndex == 0 || geneIndex == genotypeSize - 1)
			roomType = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / (DesignElement::ElementTypeCount - DesignElement::HostileTypeCount - 1)));

		designElement.setElementType((ElementType)roomType);
	}

	Individual& FI2Pop::getRandomFeasibleIndividual()
	{ 
		if (feasiblePop.getPopulationSize() > 25)
		{
			int index = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / 25));
			return this->feasiblePop.getIndividualAt(index);
		}
		else if (feasiblePop.getPopulationSize() > 20)
		{
			int index = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / 20));
			return this->feasiblePop.getIndividualAt(index);
		}
		else if (feasiblePop.getPopulationSize() > 15)
		{
			int index = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / 15));
			return this->feasiblePop.getIndividualAt(index);
		}
		else if (feasiblePop.getPopulationSize() > 10)
		{
			int index = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / 10));
			return this->feasiblePop.getIndividualAt(index);
		}
		else if (feasiblePop.getPopulationSize() > 5)
		{
			int index = static_cast<int> (rand()) / (static_cast<float> (RAND_MAX / 5));
			return this->feasiblePop.getIndividualAt(index);
		}
		else
		{
			return this->feasiblePop.getFittestIndividual();
		}
	}

}