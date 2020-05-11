#pragma once

#include <vector>
#include <stack>

#include "Node.h"

namespace Ivy
{
	/*
	 *
	 */
	class Graph
	{
	private:
		std::vector<Node> nodes{};
	public:
		Graph() = default;
		Graph(const std::vector<Node>& other);
		
		Node& getNode(int nodeId);
		void addNode(Node node);

		int getConnectivity();
		int getStrongConnectivity();
		Graph getTransposedGraph();
		void fill(int vertex, bool* visisted, std::stack<int>* stack);

		inline Graph& operator=(const Graph& other)
		{
			this->nodes = other.nodes;
			return *this;
		}
	private:
		void depthFirstSearch(int vertex, bool* visited);
		Graph(int numberOfNodes);
		

	};

}