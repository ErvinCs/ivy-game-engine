#include "ivypch.h"

#include "Individual.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Ivy {
	Individual::Individual()
	{
		this->fitness = 0;
		this->alive = true;
		this->graph = Graph();
	}

	Individual::Individual(const Individual& other)
	{
		this->designElements.clear();
		std::copy(other.designElements.begin(), other.designElements.end(), std::back_inserter(this->designElements));
		this->fitness = other.getFitness();
		this->alive = other.alive;
		this->graph = other.graph;
	}

	Individual::Individual(const std::vector<DesignElement>& designElements)
	{
		this->designElements.clear();
		std::copy(designElements.begin(), designElements.end(), std::back_inserter(this->designElements));
		this->fitness = 0;
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

	Individual& Individual::operator=(const Individual& other)
	{
		this->designElements.clear();
		std::copy(other.designElements.begin(), other.designElements.end(), std::back_inserter(this->designElements));
		this->fitness = other.getFitness();
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
				difersityFactor += 1;
			}
		}
		// Normalize the diversity factor of the 2 individuals and return it
		return (difersityFactor / designElements.size() / 2.0f);
	}

	float Individual::computeFitness()
	{
		// Returns 1.0f if there is a single longest path that connects all vertices
		// Penalizez by 1.0f / Number_Of_Vertices for each vertex that is not part of the longest path
		this->generateGraph();
		float vertexConnectivity = graph.getStrongConnectivity();
		this->fitness = 1.0f / vertexConnectivity;
		return fitness;
		/*if (vertexConnectivity != 1)
		{
			this->fitness = 1.0f / (vertexConnectivity - 1)
			return fitness;
		}
		else
		{
			this->fitness = 1.0f;
			return fitness;
		}*/
	}

	void Individual::addLeft(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		if (y != 0)
			node->addChild(graph.getNode(nodeId - 1));
	}
	void Individual::addRight(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		if (y != yMax - 1)
			node->addChild(graph.getNode(nodeId + 1));
	}
	void Individual::addTop(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		if (x != 0)
			node->addChild(graph.getNode(nodeId - xMax));
	}
	void Individual::addBottom(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		if (x != xMax)
			node->addChild(graph.getNode(nodeId + xMax));
	}

	void Individual::addNeighbours(Node* node, int nodeId, int x, int y, int xMax, int yMax)
	{
		if (x == 0)
		{
			node->addChild(graph.getNode(nodeId + xMax));	//Bellow
		}
		else if (x == xMax - 1)
		{
			node->addChild(graph.getNode(nodeId - xMax));	//Above
		}
		else
		{
			node->addChild(graph.getNode(nodeId + xMax));	//Bellow
			node->addChild(graph.getNode(nodeId - xMax));	//Above
		}
		if (y == 0)
		{
			node->addChild(graph.getNode(nodeId + 1));	//Right
		}
		else if (y == yMax - 1)
		{
			node->addChild(graph.getNode(nodeId - 1));	//Left
		}
		else
		{
			node->addChild(graph.getNode(nodeId + 1));	//Right
			node->addChild(graph.getNode(nodeId - 1));	//Left
		}
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
		nodeId = 0;
		int designElementCount = designElements.size();
		int xMax = (int)std::sqrtf(designElementCount);
		int yMax = (int)(designElementCount / xMax);
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
						if (rotation == (float)M_PI_2 || rotation == 3 * (float)M_PI_2)
						{
							/*if (x == 0)
								node->addChild(graph.getNode(nodeId + xMax));
							else if (x == xMax - 1)
								node->addChild(graph.getNode(nodeId - xMax));
							else
							{
								node->addChild(graph.getNode(nodeId + xMax));
								node->addChild(graph.getNode(nodeId - xMax));
							}*/
							addTop(node, nodeId, x, y, xMax, yMax);
							addBottom(node, nodeId, x, y, xMax, yMax);
						}
						else
						{
							/*if (y == 0)
								node->addChild(graph.getNode(nodeId + 1));
							else if (y == yMax - 1)
								node->addChild(graph.getNode(nodeId - 1));
							else
							{
								node->addChild(graph.getNode(nodeId + 1));
								node->addChild(graph.getNode(nodeId - 1));
							}*/
							addLeft(node, nodeId, x, y, xMax, yMax);
							addRight(node, nodeId, x, y, xMax, yMax);
						}
						break;
					case ElementType::VerticalWall:
						if (rotation == (float)M_PI_2)
						{
							if (x == 0)
							{
								node->addChild(graph.getNode(nodeId + xMax));	//Below
							}
							else if (x == xMax - 1)
							{
								node->addChild(graph.getNode(nodeId - xMax));	//Above
							}
							else
							{
								node->addChild(graph.getNode(nodeId + xMax));	//Below
								node->addChild(graph.getNode(nodeId - xMax));	//Above
							}
							if (y != 0)
							{
								node->addChild(graph.getNode(nodeId - 1));	//Left
							}
						}
						else if (rotation == (float)M_PI)
						{
							if (x != xMax - 1)
							{
								node->addChild(graph.getNode(nodeId + xMax));	//Below
							}
							if (y == 0)
							{
								node->addChild(graph.getNode(nodeId + 1));		//Right
							}
							else if (y == yMax - 1)
							{
								node->addChild(graph.getNode(nodeId - 1));		//Left
							}
							else
							{
								node->addChild(graph.getNode(nodeId + 1));		//Right
								node->addChild(graph.getNode(nodeId - 1));		//Left
							}
						}
						else if (rotation == 3 * (float)M_PI_2)
						{
							if (x == 0)
							{
								node->addChild(graph.getNode(nodeId + xMax));	//Below
							}
							else if (x == xMax - 1)
							{
								node->addChild(graph.getNode(nodeId - xMax));	//Above
							}
							else
							{
								node->addChild(graph.getNode(nodeId + xMax));	//Below
								node->addChild(graph.getNode(nodeId - xMax));	//Above
							}
							if (y != yMax - 1)
							{
								node->addChild(graph.getNode(nodeId + 1));	//Right
							}
						}
						else
						{
							if (x != 0)
							{
								node->addChild(graph.getNode(nodeId - xMax));	//Above
							}
							if (y == 0)
							{
								node->addChild(graph.getNode(nodeId + 1));	// Right
							}
							else if (y == yMax - 1)
							{
								node->addChild(graph.getNode(nodeId - 1));	//Left
							}
							else
							{
								node->addChild(graph.getNode(nodeId + 1));	//Right
								node->addChild(graph.getNode(nodeId - 1));	//Left
							}	
						}
						break;
					case ElementType::HorizontalWall:
						addNeighbours(node, nodeId, x, y, xMax, yMax);
						break;
					case ElementType::Pillar:
						if (rotation == (float)M_PI_2)
						{
							if (x != 0)
							{
								node->addChild(graph.getNode(nodeId - xMax));
							}
							if (y != 0)
							{
								node->addChild(graph.getNode(nodeId - 1));
							}
						}
						else if (rotation == (float)M_PI)
						{
							if (x != xMax - 1)
							{
								node->addChild(graph.getNode(nodeId + xMax));
							}
							if (y != 0)
							{
								node->addChild(graph.getNode(nodeId - 1));
							}
						}
						else if (rotation == 3.0f * (float)M_PI_2)
						{
							if (x != xMax - 1)
							{
								node->addChild(graph.getNode(nodeId + xMax));
							}
							if (y != yMax - 1)
							{
								node->addChild(graph.getNode(nodeId + 1));
							}
						}
						else
						{
							if (x != 0)
							{
								node->addChild(graph.getNode(nodeId - xMax));
							}
							if (y != yMax - 1)
							{
								node->addChild(graph.getNode(nodeId + 1));
							}
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
							if (x == 0)
							{
								node->addChild(graph.getNode(nodeId + xMax));	//Below
							}
							else if (x == xMax - 1)
							{
								node->addChild(graph.getNode(nodeId - xMax));	//Above
							}
							if (y != yMax - 1)
							{
								node->addChild(graph.getNode(nodeId - 1));	//To-Left
							}
						}
						else if (rotation == (float)M_PI)
						{
							if (x != 0)
							{
								node->addChild(graph.getNode(nodeId - xMax));	//Above
							}
							if (y == 0)
							{
								node->addChild(graph.getNode(nodeId + 1));	//To-Right
							}
							else if (y == yMax - 1)
							{
								node->addChild(graph.getNode(nodeId - 1));	//To-Left
							}
							else
							{
								node->addChild(graph.getNode(nodeId + 1));	//To-Right
								node->addChild(graph.getNode(nodeId - 1));	//To-Left
							}
						}
						else if (rotation == 3 * (float)M_PI_2)
						{
							if (y != 0)
							{
								node->addChild(graph.getNode(nodeId - 1));	//To-Left
							}
							if (x == 0)
							{
								node->addChild(graph.getNode(nodeId + xMax));	//Below
							}
							else if (x == xMax - 1)
							{
								node->addChild(graph.getNode(nodeId - xMax));	//Above
							}
							else
							{
								node->addChild(graph.getNode(nodeId - xMax));	//Above
								node->addChild(graph.getNode(nodeId + xMax));	//Below
							}
						}
						else
						{  
							if (x != xMax - 1)
							{
								node->addChild(graph.getNode(nodeId + xMax));	//Below
							}
							if (y == yMax - 1)
							{
								node->addChild(graph.getNode(nodeId - 1));	//To-Left
							}
							else if (y == 0)
							{
								node->addChild(graph.getNode(nodeId + 1));	//To-Right
							}
							else
							{
								node->addChild(graph.getNode(nodeId - 1));
								node->addChild(graph.getNode(nodeId + 1));
							}
						}
						break;
					case ElementType::ClosedRoom:
						if (rotation == 3 * (float)M_PI_2)
						{
							if (x != 0)
								node->addChild(graph.getNode(nodeId - xMax));
						}
						else if (rotation == (float)M_PI)
						{
							if (y != yMax)
								node->addChild(graph.getNode(nodeId + 1));
						}
						else if (rotation == (float)M_PI_2)
						{
							if (x != xMax)
								node->addChild(graph.getNode(nodeId + xMax));
						}
						else
						{
							if (y != 0)
								node->addChild(graph.getNode(nodeId - 1));
						}
						break;
					case ElementType::MeleeEnemy:
						if (rotation == 3 * (float)M_PI_2)
						{
							if (x != 0)
								node->addChild(graph.getNode(nodeId - xMax));
						}
						else if (rotation == (float)M_PI)
						{
							if (y != yMax)
								node->addChild(graph.getNode(nodeId + 1));
						}
						else if (rotation == (float)M_PI_2)
						{
							if (x != xMax)
								node->addChild(graph.getNode(nodeId + xMax));
						}
						else
						{
							if (y != 0)
								node->addChild(graph.getNode(nodeId - 1));
						}
						break;
					default:
						IVY_CORE_WARN("Individual: Default Generation Case! Type={0}", std::to_string(type));
					}
					nodeId++;
					it++;
				}
			}
		}
	}
	
}