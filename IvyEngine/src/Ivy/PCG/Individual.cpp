#include "ivypch.h"

#include "Individual.h"

namespace Ivy {
	Individual::Individual()
	{
		this->fitness = 0;
		this->alive = true;
	}

	Individual::Individual(const Individual& other)
	{
		std::copy(other.designElements.begin(), other.designElements.end(), std::back_inserter(this->designElements));
		this->fitness = other.getFitness();
		this->alive = true;
	}

	Individual::Individual(const std::vector<DesignElement>& designElements)
	{
		std::copy(designElements.begin(), designElements.end(), std::back_inserter(this->designElements));
		this->fitness = 0;
		this->alive = true;
	}

	void Individual::sortDesignElements()
	{
		std::sort(designElements.begin(), designElements.end());
	}

	/*
	 *
	 */
	float Individual::getDiversityFactor(Individual& other)
	{
		float difersityFactor = 0;
		for (int i = 0; i < this->designElements.size(); i++)
		{
			// Check rotation
			if (designElements[i].transform.rotation != other.getDesignElements()[i].transform.rotation)
			{
				difersityFactor += 1;
			}

			// Check tile type
			if (designElements[i].getElementType() != other.designElements[i].getElementType())
			{
				difersityFactor += 1;
			}
		}
		// Normalize the diversity factor of the 2 individuals and return it
		return (difersityFactor / designElements.size() * 2.0f);
	}

	bool Individual::operator==(Individual& other)
	{
		if (other.getDesignElements().size() <= 0)
			return false;

		for (int i = 0; i < this->designElements.size(); i++)
		{
			if (this->designElements[i] != other.getDesignElements()[i])
			{
				return false;
			}
		}
		return true;
	}

	bool Individual::operator!=(Individual& other)
	{
		return !(*this == other);
	}
}