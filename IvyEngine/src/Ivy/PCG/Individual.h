#pragma once

#include <vector>

#include "DesignElement.h"
#include "Graph.h"

namespace Ivy {
	/**
	 * An individual used in the PCG mechanism to form populations.
	 * Represents a level as an aggregation of DesignElements
	 * @see DesignElement
	 * @see Populaiton
	 */
	class Individual
	{
	private:
		std::vector<DesignElement> designElements{};
		// The ability of this individual to satisfy constraints. Domain [0,1]. Set to 1 if no constraints are violated.
		float fitness;
		// A measure of how much this individual differs from other individuals in the same population. Domain [0,1]
		float diversity;
		// Marks wether or not the individual was killed in the evolution process
		bool alive;
		// The graph that models the way in which this Individual (Level) can be traversed.
		Graph graph;
	public:
		/**
		 * Base Constructor. 
		 * Creates a live individual with fitness and diversity equalto 0 and an empty grpah.
		 */
		Individual();

		/**
		 * Copy Constructor.
		 * @param other Individual to be copied
		 */
		Individual(const Individual& other);

		/**
		 * Sets the design elements of this Individual.
		 * @param designElements vector of DesignElement to be copied into this Individual
		 */
		Individual(const std::vector<DesignElement>& designElements);

		inline std::vector<DesignElement>& getDesignElements() { return designElements; }
		inline const float& getFitness() const { return fitness; }
		inline const bool& isAlive() { return alive; }
		inline void setDesignElements(const std::vector<DesignElement>& designElements) { this->designElements = designElements; }
		inline void setFitness(const float& fitness) { this->fitness = fitness; }
		inline void setAlive(const bool& alive) { this->alive = alive; }
		inline int getDesignElementsSize() { return this->designElements.size(); }
		inline DesignElement& getDesignElementAt(int index) { return this->designElements[index]; }
		inline const float getDiversity() const { return this->diversity; }
		inline void setDiversity(const float diversity) { this->diversity = diversity; }
		inline const Graph& getGraph() { return this->graph; }

		/**
		 * @returns Graph a copy of this Individual's graph
		 */
		inline Graph copyGraph() { return this->graph; }

		/**
		 * Sorts the design elements first by the Y-Axis then by the X-Axis.
		 * @see DesignElement
		 */
		void sortDesignElements();

		/**
		 * Adds a new DesignElement to this individual.
		 * @param deisgnElement DesignElement to be added to this Individual's list
		 */
		void addDesignElement(DesignElement designElement) { designElements.push_back(designElement); }

		/**
		 * Computes the diversity of this Individual compared to another Individual.
		 * Having different rotation for a tile increases diversity by 1 measure, while having a different ElementType by 2 measures
		 * @param other Individual to compare to
		 * @returns float a normaalized diversity factor in [0,1]
		 */
		float computeDiversity(Individual& other);

		/**
		 * Computes the fitness of this Individual.
		 * The Individual is awarded a fitness of 1 if it's graph contains 1 single Strongly Connected Component.
		 * The Individual is penalized for every SCC exceeding 1.
		 * @returns float the fitness value fo this Individual
		 */
		float computeFitness();

		void generateGraph();

		/**
		 * Two individuals are equal if all their design elements are equal.
		 * @returns true if two individuals are equal and false otherwise
		 */
		bool operator==(Individual& other);

		/**
		 * Two individuals are equal if all their design elements are equal.
		 * @returns false if two individuals are equal and true otherwise
		 */
		bool operator!=(Individual& other);

		Individual& operator=(const Individual& other);

	private:
		// Add neighbouring nodes to the left, right, top, bottom of a node in this individual
		void addNeighbours(Node* node, int nodeId, int x, int y, int xMax, int yMax);
		void addLeft(Node* node, int nodeId, int x, int y, int xMax, int yMax);
		void addRight(Node* node, int nodeId, int x, int y, int xMax, int yMax);
		void addTop(Node* node, int nodeId, int x, int y, int xMax, int yMax);
		void addBottom(Node* node, int nodeId, int x, int y, int xMax, int yMax);

		// Remove a neighbouring node of a node in this individual
		void removeLeft(Node* node, int nodeId, int x, int y, int xMax, int yMax);
		void removeRight(Node* node, int nodeId, int x, int y, int xMax, int yMax);
		void removeTop(Node* node, int nodeId, int x, int y, int xMax, int yMax);
		void removeBottom(Node* node, int nodeId, int x, int y, int xMax, int yMax);
	};
}