#include "ivypch.h"

#include "Population.h"

namespace Ivy {

	Population::Population(const Population& other)
	{
		this->individuals.clear();
		std::copy(other.getIndividualsConst().begin(), other.getIndividualsConst().end(), std::back_inserter(this->individuals));
	}

	Population::Population(const std::vector<Individual>& individualList)
	{
		this->individuals.clear();
		std::copy(individualList.begin(), individualList.end(), std::back_inserter(this->individuals));
	}

	Individual Population::getMostFitAndDiverseIndividual()
	{
		Individual best = individuals[0];
		for (int i = 0; i < individuals.size(); i++)
		{
			if (individuals[i].getFitness() > best.getFitness())
			{
				if(individuals[i].getDiversity() > best.getDiversity())
					best = individuals[i];
			}
		}
		return best;
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
		std::sort(individuals.begin(), individuals.end(), [](Individual ind1, Individual ind2) {
			return ind1.getFitness() > ind2.getFitness();
		});
	}

	void Population::addIndividual(const Individual& individual)
	{
		this->individuals.push_back(individual);
	}

	void Population::removeIndividualAtIndex(int index)
	{
		this->individuals.erase(individuals.begin() + index);
	}

	Individual& Population::getIndividualAt(int index)
	{
		return this->individuals[index];
	}

	Population& Population::Population::operator=(const Population& other)
	{
		this->individuals.clear();
		std::copy(other.getIndividualsConst().begin(), other.getIndividualsConst().end(), std::back_inserter(this->individuals));
		return *this;
	}
}