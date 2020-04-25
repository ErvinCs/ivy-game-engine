#include "ivypch.h"
#include "Graph.h"

#include "../Core/Logger.h"

namespace Ivy
{
	Graph::Graph(const std::vector<Node>& other)
	{
		this->nodes = other;
	}

	Graph::Graph(int numberOfNodes)
	{
		for (int i = 0; i < numberOfNodes; i++)
		{
			this->nodes.emplace_back(Node(i));
		}
	}

	Node& Graph::getNode(int nodeId)
	{
		return this->nodes[nodeId];
	}

	void Graph::addNode(Node node)
	{
		this->nodes.push_back(node);
	}

	// Returns the number of connected components
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
	// Returns the number of strongly connected components - should be 1 for a feasible graph
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
				fill(i, visited, &stack);
			}
		}

		// Process the vertices in the order they were added in the stack
		Graph transposedGrpah = this->getTransposedGraph();

		for (int i = 0; i < nodesSize; i++)
		{
			visited[i] = false;
		}

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
		Graph transposedGraph = Graph(this->nodes.size());
		
		int numberOfNodes = this->nodes.size();
		for (int i = 0; i < numberOfNodes; i++)
		{
			std::vector<Node> childNodes = this->nodes[i].getChildren();
			int childNodesSize = childNodes.size();
			for (int j = 0; j < childNodesSize; j++)
			{
				int childNodeId = childNodes[j].getNodeId();
				transposedGraph.nodes[childNodeId].addChild(Node(i));
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
			{
				depthFirstSearch(node.getNodeId(), visited);	
			}
		}
	}

	void Graph::fill(int vertex, bool* visited, std::stack<int>* stack)
	{
		visited[vertex] = true;
		for (Node& node : nodes[vertex].getChildren())
		{
			if (!visited[node.getNodeId()])
				fill(node.getNodeId(), visited, stack);
		}
		stack->push(vertex);
	}

}