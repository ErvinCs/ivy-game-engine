#include "ivypch.h"
#include "Graph.h"


namespace Ivy
{
	Graph::Graph(const std::vector<Node>& other)
	{
		this->nodes = other;
	}

	Node& Graph::getNode(const std::string & nodeName)
	{
		for (auto& it = nodes.begin(); it != nodes.end(); it++)
		{
			Node& node = *it;
			if(node.getNodeName() == nodeName)
				return *it;
		}
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

	int Graph::getNumberOfConnections()
	{
		int numberOfConnections = 0;
		for (Node& node : nodes)
		{
			for (Node& node : node.getChildren())
			{
				numberOfConnections += 1;
			}
		}
		return numberOfConnections;
	}

	int Graph::getVertexConnections(int nodeId)
	{
		return this->getNode(nodeId).getChildren().size();
	}

	bool Graph::isKVertexConnected()
	{
		for (Node& node : nodes)
		{
			// If the node has more children than the connectivity factor than it is not k connected
			if (kConnectivityFactor > node.getChildren().size())
			{
				return false;
			}
		}
		return true;
	}

	int Graph::getKConnectivity()
	{
		int currKConnectivity = 0;
		for (Node& node : nodes)
		{
			// If the node has more children than the connectivity factor than it is not k connected
			if (node.getChildren().size() >= kConnectivityFactor)
			{
				currKConnectivity += 1;
			}
		}
		return currKConnectivity;
	}

	int Graph::getVariableKConnectivity()
	{
		int varKConnectivity;
		for (Node& node : nodes)
		{
			// If the node has more children than the connectivity factor than it is not k connected
			varKConnectivity += node.getChildren().size();
		}
		return varKConnectivity;
	}

	int Graph::getConnectivity()
	{
		int connectedComponents = 0;
		const int nodesSize = nodes.size();
		bool* visited = new bool[nodesSize];

		for (int i = 0; i < nodesSize; i++)
		{
			visited[i] = false;
		}

		for (int i = 0; i < nodesSize; i++)
		{
			if (visited[i] == false)
			{
				depthFirstSearch(i, visited);
				connectedComponents += 1;
			}
		}

		delete[] visited;
		return connectedComponents;
	}

	// Using Kosaraju Algorithm
	int Graph::getStrongConnectivity()
	{
		int strongConnectedComponents = 0;
		std::stack<int> stack{};
		const int nodesSize = nodes.size();
		bool* visited = new bool[nodesSize];

		// Find reachable vertices
		for (int i = 0; i < nodesSize; i++)
		{
			visited[i] = false;
		}

		for (int i = 0; i < nodesSize; i++)
		{
			if (visited[i] == false)
			{
				fill(i, visited, stack);
			}
		}

		// Process the vertices in the order they were added in the stack
		Graph transposedGrpah = this->getTransposedGraph();

		while (stack.size() > 0)
		{
			int vertex = stack.top();
			stack.pop();

			if (visited[vertex] == false)
			{
				transposedGrpah.depthFirstSearch(vertex, visited);
				strongConnectedComponents += 1;
			}
		}

		delete[] visited;
		return strongConnectedComponents;
	}

	Graph Graph::getTransposedGraph()
	{
		Graph transposedGraph = Graph();
		for (int i = 0; i < nodes.size(); i++)
		{
			for (const Node& node : nodes)
			{
				transposedGraph.nodes.push_back(node);
			}
		}
		return transposedGraph;
	}

	void Graph::depthFirstSearch(int vertex, bool* visited)
	{
		visited[vertex] = true;
		for (Node& node : nodes[vertex].getChildren())
		{
			if (!visited[node.getNodeId()])
				depthFirstSearch(node.getNodeId(), visited);
		}
	}

	void Graph::fill(int vertex, bool* visited, std::stack<int>& stack)
	{
		visited[vertex] = true;
		for (Node& node : nodes[vertex].getChildren())
		{
			if (!visited[node.getNodeId()])
				fill(node.getNodeId(), visited, stack);
		}
	}





}