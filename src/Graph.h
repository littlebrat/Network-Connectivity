#ifndef GRAPH_H
#define GRAPH_H

#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include <queue>

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

		// defines the default flow of the links in the graph
		const static Link::Flow DEFAULT_FLOW = 1;

		/*
		 * Allows that Graph objects can be printed in the same form as other types.
		 * (e.g. std::cout << graph << std::endl)
		 * It must be a friend method because it needs to access private members
		 */
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

		/*
		 * These methods should be used to access the negative and positive nodes of a specific super node.
		 * They receive the super node id and return the node in the graph negative or positive according
		 * to the called method.
		 */
		inline NodePtr& negNode(Node::ID id) { return nodes[2 * id]; }
		inline NodePtr& posNode(Node::ID id) { return nodes[2 * id + 1]; }
		inline Node::ID index(Node* node) {
			return (Node::ID) (node->polarity == Node::Polarity::Negative ? 2 * node->id : 2 * node->id + 1);
		}

		bool getPath(Node::ID start_node, Node::ID goal_node, Node* parents[]);
	};

}


#endif //GRAPH_H
