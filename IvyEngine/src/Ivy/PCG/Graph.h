#pragma once

#include <vector>
#include <stack>

#include "Node.h"

namespace Ivy {
	/**
	 * A directed graph represented as a list of Nodes
	 * @see Node
	 */
	class Graph
	{
	private:
		std::vector<Node> nodes{};
	public:
		// Default Constructor
		Graph() = default;

		/**
		 * Create a graph with the given nodes
		 * @param other Vector of nodes
		 */
		Graph(const std::vector<Node>& other);
		
		/**
		 * Returns the Node with the given id
		 * @param nodeId int representing the id of the Node to be recovered
		 * @returns Node with the given id
		 */
		Node& getNode(int nodeId);

		/**
		 * Add a new node to this graph.
		 * @param node Node to be added to the graph
		 */
		void addNode(Node node);

		/**
		 * Performs DFS to determine the number of connected components
		 * @returns int the number of connected componets
		 */
		int getConnectivity();

		/**
		 * (Kosaraju's Algorithm)
		 * Constructs a stack in order inverse to the order they can be reached from an arbitrary starting vertex.
		 * Then transposes the graph and performs DFS starting with the vertex on the top of the stack.
		 * The number of SCCs is equal to the number of times a DFS is started.
		 * @returns int the number of strongly connected components
		 */
		int getStrongConnectivity();

		/**
		 * Creates and returns a new graph where all the edges of this Graph are inverted
		 * @returns Graph transposed
		 */
		Graph getTransposedGraph();

		/**
		 * Starting with a given vertex the algorithm tries to reach all the reachable vertices from it.
		 * It creates a stack by adding the vertices in it inverse to the order they were reached.
		 * It also creates an array that represents which vertices were visited
		 * @param vertex (in) starting vertex
		 * @param visited (out) the array of visited vertices
		 * @param stack (out) the stack of visited vertices
		 */
		void fill(int vertex, bool* visisted, std::stack<int>* stack);

		/**
		 * Assigns the value of another graph to this graph.
		 * @param other Graph to be copied
		 * @returns Graph
		 */
		inline Graph& operator=(const Graph& other)
		{
			this->nodes = other.nodes;
			return *this;
		}
	private:
		void depthFirstSearch(int vertex, bool* visited);

		/**
		 * Constructs a graph with the given number of nodes and no edges
		 * @param numberOfNodes int representing the number of nodes to be created
		 */
		Graph(int numberOfNodes);
	};
}