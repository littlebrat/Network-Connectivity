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

	class Path;

	class Graph {

		friend class Path;

	public:
		typedef std::unique_ptr<Node> NodePtr;
		// a node list stores all nodes with Negative and Positive polarity
		typedef std::array<NodePtr, 2 * (Node::MAX_ID + 1)> NodeHolder;
		// type for the indexes of each node in the graph
		typedef uint16_t Index;

	public: // class methods

		Graph();
		Graph(const std::string& filename);

		void addEdge(Node::ID srcNode, Node::ID destNode);
		inline size_t size() const { return nodeCount / 2; }

	private:
		NodeHolder nodes;   // stores all the nodes in the graph
		size_t nodeCount;   // number of actual node in the graph (its the number of nodes and ot super nodes

		/*
		 * Allows that Graph objects can be printed in the same form as other types.
		 * (e.g. std::cout << graph << std::endl)
		 * It must be a friend method because it needs to access private members
		 */
		friend std::ostream& operator<<(std::ostream& out, const Graph& graph) {
			using namespace std;

			out << "Graph" << endl;
			for(auto& node : graph.nodes) {
				if(node != nullptr) {
					out << *node << "[ ";

					for (auto& link : node->getLinks()) {
						out << link << " ";
					}
					out << "]" << endl;
				}
			}

			return out;
		}

		void createSupernode(Node::ID nodeId);

		/*
		 * These methods should be used to access the negative and positive nodes of a specific supernode.
		 * They receive the supernode id and return the node in the graph negative or positive according
		 * to the called method.
		 */
		inline NodePtr& negNode(Node::ID id) { return nodes[2 * id]; }
		inline NodePtr& posNode(Node::ID id) { return nodes[2 * id + 1]; }

		bool getPath(Node::ID start_node, Node::ID goal_node, std::vector<Node*>& parents);
	};

	inline Graph::Index index(const Node* node) {
		return (Graph::Index) (node->getPolarity() == Node::Polarity::Negative ?
		                                              2 * node->getId() : 2 * node->getId() + 1);
	}

}


#endif //GRAPH_H
