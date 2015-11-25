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
		typedef std::array<NodePtr, (2 * Node::MAX_ID + 1)> NodeHolder;

		Graph();
		Graph(std::string filename);

		void addEdge(Node::ID srcNode, Node::ID destNode);

	private:
		NodeHolder nodes;     // stores all the nodes in the graph

		const static Link::Flow DEFAULT_FLOW = 1;

		friend std::ostream& operator<<(std::ostream& out, const Graph& graph) {
			using namespace std;

			out << "Graph" << endl;
			for(auto& node : graph.nodes) {
				out << *node << "[ ";

				for(auto& link : node->getLinks()) {
					out << link << " ";
				}
				out << "]" << endl;
			}

			return out;
		}

		inline NodePtr& negNode(Node::ID id) { return nodes[2 * id]; }
		inline NodePtr& posNode(Node::ID id) { return nodes[2 * id + 1]; }
	};

}


#endif //GRAPH_H
