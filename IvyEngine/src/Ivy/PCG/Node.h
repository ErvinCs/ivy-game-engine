#pragma once

#include <vector>
#include <string>

namespace Ivy {
	/**
	 * A node in a directed graph.
	 * Encapsulates a unique identifier and a list of its children
	 */
	class Node
	{
	private:		
		int nodeId;
		std::vector<Node> children{};
	public:
		/**
		 * Default Constructor.
		 * Sets nodeId to -1.
		 */
		Node()
		{
			this->nodeId = -1;
		}

		/**
		 * Constructs a node with a given Id.
		 * @param nodeId the Id of this node
		 */
		Node(int nodeId)
		{
			this->nodeId = nodeId;
		}

		/**
		 * Copy Constructor
		 * @param other Node to copy
		 */
		Node(const Node& other)
		{
			this->nodeId = other.nodeId;
			std::copy(other.children.begin(), other.children.end(), std::back_inserter(this->children));
		}

		inline int getNodeId() { return this->nodeId; }
		inline void setNodeId(int nodeId) { this->nodeId = nodeId; }
		inline std::vector<Node>& getChildren() { return this->children; }

		/**
		 * Adds a child node to this node.
		 * @param node to be added as a child of this node
		 */
		inline void addChild(Node node) { this->children.push_back(node); }

		/**
		 * Removes a child node fo this node.
		 * @param node to be removed from the children kept by this node
		 */
		inline void removeChild(Node& node) 
		{
			auto& it = std::find(children.begin(), children.end(), node);
			if (it != children.end())
				this->children.erase(it);
		}

		/**
		 * @param other Node
		 * @returns true if the id of this node is equal to the other's and false otherwise
		 */
		inline bool operator==(const Node& other)
		{
			return this->nodeId == other.nodeId;
		}

		/**
		 * @param other Node
		 * @returns false if the id of this node is equal to the other's and true otherwise
		 */
		inline bool operator!=(const Node& other)
		{
			return (!(*this == other));
		}
	};
}