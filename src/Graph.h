#ifndef GRAPH_H
#define GRAPH_H

#include <cstdint>
#include <vector>
#include <string>
#include <memory>

#include "Node.h"
#include "Link.h"

namespace Network {

	class Graph {

	public:

		typedef std::unique_ptr<Node> NodePtr;
		// a node list stores all nodes with Negative and Positive polarity
		typedef std::array<NodePtr, (2 * Node::MAX_ID + 1)> NodeList;
		typedef std::unique_ptr<Link> LinkPtr;
		typedef std::array<LinkPtr, (2 * Node::MAX_ID + 1)> LinkList;

		Graph();
		Graph(std::string filename);

		void addLink(Node::ID srcNode, Node::ID destNode);

	private:
		NodeList nodes;     // stores all the nodes in the graph
		LinkList links;     // stores all the links in the graph

	};

}


#endif //GRAPH_H
