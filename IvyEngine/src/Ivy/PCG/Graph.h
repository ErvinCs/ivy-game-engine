#pragma once

#include <vector>
#include <stack>

#include "Node.h"

namespace Ivy
{

	class Graph
	{
	private:
		std::vector<Node> nodes{};
		const int kConnectivityFactor = 2;
	public:
		Graph() = default;
		Graph(const std::vector<Node>& other);
		
		Node& getNode(const std::string& nodeName);
		Node& getNode(int nodeId);
		
		int getNumberOfConnections();
		int getVertexConnections(int nodeId);
		bool isKVertexConnected();
		int getKConnectivity();
		int getVariableKConnectivity();
		int getConnectivity();
		int getStrongConnectivity();
		Graph getTransposedGraph();

		void addNode(Node& node);
		void addEdge(Node& from, Node& to);

		inline Graph& operator=(const Graph& other)
		{
			this->nodes = other.nodes;
			return *this;
		}
	private:
		void depthFirstSearch(int vertex, bool* visited);
		void fill(int vertex, bool* visisted, std::stack<int>& stack);

	};

}