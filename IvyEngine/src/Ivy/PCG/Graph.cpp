#include "ivypch.h"
#include "Graph.h"

#include "../Core/Logger.h"

namespace Ivy
{
	Graph::Graph(const std::vector<Node>& other)
	{
		this->nodes = other;
	}

	Node& Graph::getNode(int nodeId)
	{
		for (auto& it = nodes.begin(); it != nodes.end(); it++)
		{
			Node& node = *it;
			if (node.getNodeId() == nodeId)
				return *it;
		}
	}

	void Graph::addNode(Node node)
	{
		this->nodes.push_back(node);
	}

	int Graph::getConnectivity()
	{
		int connectedComponents = 0;
		const int nodesSize = nodes.size();
		bool* visited = new bool[nodesSize];
		int* longestPath = new int;
		*longestPath = 0;
		int* currPath = new int;
		*currPath = 0;

		for (int i = 0; i < nodesSize; i++)
		{
			visited[i] = false;
		}

		for (int i = 0; i < nodesSize; i++)
		{
			//IVY_CORE_TRACE("Graph: LongestPath={0}", *longestPath);
			if (visited[i] == false)
			{
				depthFirstSearch(i, visited, currPath);
				connectedComponents += 1;
				if (*currPath > *longestPath)
					*longestPath = *currPath;
				*currPath = 0;
			}
			if (*longestPath == maximumPath)
				break;
		}

		int result = *longestPath;
		delete longestPath;
		delete currPath;
		delete[] visited;
		return result;
	}

	void Graph::depthFirstSearch(int vertex, bool* visited, int* currPath)
	{
		visited[vertex] = true;
		for (Node& node : nodes[vertex].getChildren())
		{
			if (!visited[node.getNodeId()])
			{
				*currPath += 1;
				depthFirstSearch(node.getNodeId(), visited, currPath);
			}
		}
	}

}