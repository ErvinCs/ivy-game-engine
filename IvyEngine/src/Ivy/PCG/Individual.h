#pragma once

#include <vector>

#include "DesignElement.h"
#include "Graph.h"

namespace Ivy {
	class Individual
	{
	private:
		std::vector<DesignElement> designElements{};
		float fitness;
		float diversity;
		bool alive;
		Graph graph;
	public:
		Individual();
		Individual(const Individual& other);
		Individual(const std::vector<DesignElement>& designElements);

		inline std::vector<DesignElement>& getDesignElements() { return designElements; }
		inline const float& getFitness() const { return fitness; }
		inline const bool& isAlive() { return alive; }
		inline void setDesignElements(const std::vector<DesignElement>& designElements) { this->designElements = designElements; }
		inline void setFitness(const float& fitness) { this->fitness = fitness; }
		inline void setAlive(const bool& alive) { this->alive = alive; }
		inline const Graph& getGraph() { return this->graph; }
		inline int getDesignElementsSize() { return this->designElements.size(); }
		inline DesignElement& getDesignElementAt(int index) { return this->designElements[index]; }
		inline Graph copyGraph() { return this->graph; }
		inline float getDiversity() { return this->diversity; }
		inline void setDiversity(float diversity) { this->diversity = diversity; }

		void sortDesignElements();
		void addDesignElement(DesignElement designElement) { designElements.push_back(designElement); }

		float computeDiversity(Individual& other);
		float computeFitness();

		void generateGraph();
		void addNeighbours(Node* node, int nodeId, int x, int y, int xMax, int yMax);

		/*
		 * Two individuals are equal if all their design elements are equal.
		 * Returns true if two individuals are equal and false otherwise
		 */
		bool operator==(Individual& other);
		bool operator!=(Individual& other);

		Individual& operator=(const Individual& other);
		
		
	};
}