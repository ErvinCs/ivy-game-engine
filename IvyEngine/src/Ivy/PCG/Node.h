#pragma once

#include <vector>
#include <string>

namespace Ivy
{
	class Node
	{
	private:
		std::string nodeName;
		int nodeId;
		std::vector<Node> children;
	public:
		Node()
		{
			this->nodeName = "";
			this->nodeId = -1;

		}
		Node(std::string nodeName, int nodeId)
		{
			this->nodeName = nodeName;
			this->nodeId = nodeId;
		}

		inline const std::string& getNodeName() { return this->nodeName; }
		inline int getNodeId() { return this->nodeId; }
		inline void setNodeName() { this->nodeName = nodeName; }
		inline void setNodeId(int nodeId) { this->nodeId = nodeId; }
		inline std::vector<Node>& getChildren() { return this->children; }
		inline void addChild(const Node& node) { this->children.push_back(node); }
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