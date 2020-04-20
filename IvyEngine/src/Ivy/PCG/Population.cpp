#include "ivypch.h"

#include "Population.h"

namespace Ivy {

	Population::Population(Population& other)
	{
		std::copy(other.getIndividuals().begin(), other.getIndividuals().end(), std::back_inserter(this->individuals));
	}

	Population::Population(const std::vector<Individual>& individualList)
	{
		std::copy(individualList.begin(), individualList.end(), std::back_inserter(this->individuals));
	}

	Individual Population::getFittestIndividual()
	{
		Individual fittest = individuals[0];
		for (int i = 0; i < individuals.size(); i++)
		{
			if (individuals[i].getFitness() > fittest.getFitness())
				fittest = individuals[i];
		}
		return fittest;
	}

	Individual Population::getLeastFitIndividual()
	{
		Individual leastFit = individuals[0];
		for (int i = 0; i < individuals.size(); i++)
		{
			if (individuals[i].getFitness() < leastFit.getFitness())
				leastFit = individuals[i];
		}
		return leastFit;
	}

	int Population::getLeastFitIndividualIndex()
	{
		Individual leastFit = individuals[0];
		int index = 0;
		for (int i = 0; i < individuals.size(); i++)
		{
			if (individuals[i].getFitness() < leastFit.getFitness())
			{
				leastFit = individuals[i];
				index = i;
			}
		}
		return index;
	}

	int Population::getPopulationSize()
	{
		return this->individuals.size();
	}

	void Population::sortIndividuals()
	{
		for (int i = 0; i < individuals.size(); i++)
		{
			individuals[i].sortDesignElements();
		}
	}

	void Population::addIndividual(const Individual& individual)
	{
		this->individuals.push_back(individual);
	}

	void Population::removeIndividualAtIndex(int index)
	{
		this->individuals.erase(individuals.begin() + index);
	}

	void Population::removeDeadIndividuals()
	{
		for (auto& it = individuals.begin(); it < individuals.end(); it++)
		{
			Individual& ind = *it;
			if (!ind.isAlive())
				individuals.erase(it);
		}
	}

}