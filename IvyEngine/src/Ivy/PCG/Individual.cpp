#include "ivypch.h"

#include "Individual.h"
#include "DesignElements/LevelElement.h"

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

	Individual::Individual(const std::vector<DesignElement*>& designElements)
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
			if (designElements[i]->transform.rotation != other.getDesignElements()[i]->transform.rotation)
			{
				difersityFactor += 1;
			}

			// Check tile type
			if (((LevelElement*)designElements[i])->getElementType() != ((LevelElement*)other.designElements[i])->getElementType())
			{
				difersityFactor += 1;
			}
		}
		// Normalize the diversity factor of the 2 individuals and return it
		return (difersityFactor / designElements.size() * 2.0f);
	}

	/*
	 *
	 */
	float Individual::getLinearityFactor()
	{
		/*for (DesignElement* element : designElements)
		{
			int type = (int)element->getElementType();
			if (!(type < DesignElement::ElementTypeCount))
				continue;
			//...
		}
		//...
		float min = 15 / designElements.size();
		float max = 0, maxValue = 0;
		for (auto SOMETHING : ...)
		{
			if (SOMETHING.size() > max)
			{
				max = SOMETHING.size();
				max = SOMETHING.value;
			}
		}
		float linearity = 0;
		if (max > min)
			linearity = max / designElements.size();
		return linearity;*/
		return 0.0f;
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