#include "ivypch.h"

#include "Individual.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Ivy {
	Individual::Individual()
	{
		this->fitness = 0;
		this->diversity = 0;
		this->alive = true;
		this->graph = Graph();
	}

	Individual::Individual(const Individual& other)
	{
		this->designElements.clear();
		std::copy(other.designElements.begin(), other.designElements.end(), std::back_inserter(this->designElements));
		this->fitness = other.getFitness();
		this->diversity = other.getDiversity();
		this->alive = other.alive;
		this->graph = other.graph;
	}

	Individual::Individual(const std::vector<DesignElement>& designElements)
	{
		this->designElements.clear();
		std::copy(designElements.begin(), designElements.end(), std::back_inserter(this->designElements));
		this->fitness = 0;
		this->diversity = 0;
		this->alive = true;
		this->graph = Graph();
	}

	void Individual::sortDesignElements()
	{
		std::sort(designElements.begin(), designElements.end());
	}

	bool Individual::operator==(Individual& other)
	{
		if (other.getDesignElements().size() <= 0)
			return false;

		for (int i = 0; i < this->designElements.size(); i++)
		{
			if (this->designElements[i] != other.getDesignElementAt(i))
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

	Individual& Individual::operator=(const Individual& other)
	{
		this->designElements.clear();
		std::copy(other.designElements.begin(), other.designElements.end(), std::back_inserter(this->designElements));
		this->fitness = other.getFitness();
		this->diversity = other.getDiversity();
		this->alive = other.alive;
		this->graph = other.graph;
		return *this;
	}

	float Individual::computeDiversity(Individual& other)
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
				difersityFactor += 2;
			}
		}
		// Normalize the diversity factor of the 2 individuals and return it
		return ((difersityFactor / ((float)designElements.size() * 3.0f)));
	}

	float Individual::computeFitness()
	{
		// Returns 1.0f if there is a single longest path that connects all vertices
		this->generateGraph();
		float numberOfVerteices = this->getDesignElementsSize();
		float vertexConnectivity = graph.getStrongConnectivity();
		if (vertexConnectivity == 1)
		{
			this->fitness = 1.0f;
			return fitness;
		}
		else
		{
			fitness = (((numberOfVerteices - vertexConnectivity) / numberOfVerteices) + (1.0f / numberOfVerteices));
			return fitness;
		}
	}

	// Add children
	void Individual::addLeft(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		if (x != 0)
			node->addChild(graph.getNode(nodeId - yMax));
	}
	void Individual::addRight(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		if (x != xMax - 1)
			node->addChild(graph.getNode(nodeId + yMax));
	}
	void Individual::addTop(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		if (y != yMax - 1)
			node->addChild(graph.getNode(nodeId + 1));
	}
	void Individual::addBottom(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		if (y != 0)
			node->addChild(graph.getNode(nodeId - 1));
	}

	// Remove impossible children
	void Individual::removeLeft(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		node->removeChild(nodeId - yMax);
	}
	void Individual::removeRight(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		node->removeChild(nodeId + yMax);
	}
	void Individual::removeTop(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		node->removeChild(nodeId + 1);
	}
	void Individual::removeBottom(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		node->removeChild(nodeId - 1);
	}

	/*
	 *   3       7     11
	 * (x0y3) (x1y3) (x2y3)
	 *   2       6	   10
	 * (x0y2) (x1y2) (x2y2)
	 *   1       5	    9
	 * (x0y1) (x1y1) (x2y1)
	 *   0       4	    8
	 * (x0y0) (x1y0) (x2y0)
	 *
	 * yMax = 4
	 * xMax = 3
	 */
	void Individual::addNeighbours(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		addLeft(node, nodeId, x, y, xMax, yMax);
		addTop(node, nodeId, x, y, xMax, yMax);
		addBottom(node, nodeId, x, y, xMax, yMax);
		addRight(node, nodeId, x, y, xMax, yMax);
	}

	void Individual::generateGraph()
	{
		this->graph = Graph();
		int nodeId = 0;
		for (auto& it = designElements.begin(); it != designElements.end(); it++)
		{
			graph.addNode(Node(nodeId));
			nodeId++;
		}
		
		int designElementCount = designElements.size();
		int xMax = (int)std::sqrtf(designElementCount);
		int yMax = (int)(designElementCount / xMax);

		// Add possible children
		nodeId = 0;
		auto& it = designElements.begin();
		for (int x = 0; x < (int)xMax; x++)
		{
			for (int y = 0; y < (int)yMax; y++)
			{
				if (it != designElements.end())
				{
					Node* node = &graph.getNode(nodeId);
					DesignElement& levelElement = *it;
					ElementType type = levelElement.getElementType();
					float rotation = levelElement.transform.rotation;

					switch (type)
					{
					case ElementType::Hallway:
						if (rotation == (float)M_PI_2 || rotation == 3.0f * (float)M_PI_2)
						{
							addTop(node, nodeId, x, y, xMax, yMax);
							addBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI || rotation == 0)
						{
							addLeft(node, nodeId, x, y, xMax, yMax);
							addRight(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for VerticalWall!");
						}
						break;
					case ElementType::VerticalWall:
						if (rotation == (float)M_PI_2)
						{
							addLeft(node, nodeId, x, y, xMax, yMax);
							addTop(node, nodeId, x, y, xMax, yMax);
							addBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI)
						{
							addBottom(node, nodeId, x, y, xMax, yMax);
							addLeft(node, nodeId, x, y, xMax, yMax);
							addRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							addTop(node, nodeId, x, y, xMax, yMax);
							addBottom(node, nodeId, x, y, xMax, yMax);
							addRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 0)
						{
							addTop(node, nodeId, x, y, xMax, yMax);
							addLeft(node, nodeId, x, y, xMax, yMax);
							addRight(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for VerticalWall!");
						}
						break;
					case ElementType::HorizontalWall:
						addNeighbours(node, nodeId, x, y, xMax, yMax);
						break;
					case ElementType::Pillar:
						if (rotation == (float)M_PI_2)
						{
							addTop(node, nodeId, x, y, xMax, yMax);
							addLeft(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI)
						{
							addLeft(node, nodeId, x, y, xMax, yMax);
							addBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							addRight(node, nodeId, x, y, xMax, yMax);
							addBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 0)
						{
							addRight(node, nodeId, x, y, xMax, yMax);
							addTop(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for Pillar!");
						}
						break;
					case ElementType::Hole:
						addNeighbours(node, nodeId, x, y, xMax, yMax);
						break;
					case ElementType::RangedEnemy:
						addNeighbours(node, nodeId, x, y, xMax, yMax);
						break;
					case ElementType::StandardRoom1:
						addNeighbours(node, nodeId, x, y, xMax, yMax);
						break;
					case ElementType::StandardRoom2:
						addNeighbours(node, nodeId, x, y, xMax, yMax);
						break;
					case ElementType::TShaped:
						if (rotation == (float)M_PI_2)
						{
							addTop(node, nodeId, x, y, xMax, yMax);
							addBottom(node, nodeId, x, y, xMax, yMax);
							addRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI)
						{
							addTop(node, nodeId, x, y, xMax, yMax);
							addRight(node, nodeId, x, y, xMax, yMax);
							addLeft(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							addTop(node, nodeId, x, y, xMax, yMax);
							addBottom(node, nodeId, x, y, xMax, yMax);
							addLeft(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 0)
						{  
							addBottom(node, nodeId, x, y, xMax, yMax);
							addRight(node, nodeId, x, y, xMax, yMax);
							addLeft(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for T-Shaped!");
						}
						break;
					case ElementType::ClosedRoom:
						if (rotation == (float)M_PI_2)
						{
							addBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI)
						{
							addRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							addTop(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 0)
						{
							addLeft(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for Closed Room!");
						}
						break;
					case ElementType::MeleeEnemy:
						if (rotation == (float)M_PI_2)
						{
							addBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI)
						{
							addRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							addTop(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 0)
						{
							addLeft(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for MeleeEnemy!");
						}
						break;
					default:
						IVY_CORE_WARN("Individual: Default Generation Case! Type={0}", std::to_string(type));
						break;
					}
					nodeId++;
					it++;
				}
			}
		}

		// Remove impossible children
		nodeId = 0;
		it = designElements.begin();
		for (int x = 0; x < (int)xMax; x++)
		{
			for (int y = 0; y < (int)yMax; y++)
			{
				if (it != designElements.end())
				{
					Node* node = &graph.getNode(nodeId);
					DesignElement& levelElement = *it;
					ElementType type = levelElement.getElementType();
					float rotation = levelElement.transform.rotation;

					switch (type)
					{
					case ElementType::Hallway:
						if (rotation == (float)M_PI_2 || rotation == 3.0f * (float)M_PI_2)
						{
							//Remove Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI || rotation == 0)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for VerticalWall!");
						}
						break;
					case ElementType::VerticalWall:
						if (rotation == (float)M_PI_2)
						{
							//Remove Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 0)
						{
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for VerticalWall!");
						}
						break;
					case ElementType::Pillar:
						if (rotation == (float)M_PI_2)
						{
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
							//Remve Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 0)
						{
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
							//Remove Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for Pillar!");
						}
						break;
					case ElementType::TShaped:
						if (rotation == (float)M_PI_2)
						{
							//Remove Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI)
						{
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 0)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for T-Shaped!");
						}
						break;
					case ElementType::ClosedRoom:
						if (rotation == (float)M_PI_2)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
							//Remove Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
							//Remove Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							//Remove Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 0)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for Closed Room!");
						}
						break;
					case ElementType::MeleeEnemy:
						if (rotation == (float)M_PI_2)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
							//Remove Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == (float)M_PI)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
							//Remove Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							//Remove Left
							removeLeft(node, nodeId, x, y, xMax, yMax);
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
						}
						else if (rotation == 0)
						{
							//Remove Top
							removeTop(node, nodeId, x, y, xMax, yMax);
							//Remove Right
							removeRight(node, nodeId, x, y, xMax, yMax);
							//Remove Bot
							removeBottom(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							IVY_CORE_WARN("Individual: No rotation case reached for Closed Room!");
						}
						break;
					default:
						//IVY_CORE_TRACE("Individual: No Edges to remove", std::to_string(type));
						break;
					}
					nodeId++;
					it++;
				}
			}
		}
	}
	
}