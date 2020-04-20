#pragma once

#include <vector>
#include <string>

namespace Ivy
{
	class Node
	{
	private:
		int nodeId;
		std::vector<Node> children{};
	public:
		Node()
		{
			this->nodeId = -1;
		}

		Node(int nodeId)
		{
			this->nodeId = nodeId;
		}

		Node(const Node& other)
		{
			this->nodeId = other.nodeId;
			std::copy(other.children.begin(), other.children.end(), std::back_inserter(this->children));
		}

		inline int getNodeId() { return this->nodeId; }
		inline void setNodeId(int nodeId) { this->nodeId = nodeId; }
		inline std::vector<Node>& getChildren() { return this->children; }
		inline void addChild(Node node) { this->children.push_back(node); }
		inline void removeChild(int nodeId) 
		{
			for (auto& it = children.begin(); it != children.end(); it++)
			{
				Node& node = *it;
				if (node.getNodeId() == this->nodeId)
					children.erase(it);
			}
		}
	};

}