#ifndef GRAPH_H
#define GRAPH_H

#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include <queue>

#include "Node.h"
#include "Link.h"
#include "Subnode.h"
#include "NetworkIdGenerator.h"

namespace Network {

	class Graph {

		typedef std::unique_ptr<Node> NodeOwner;
		typedef std::vector<NodeOwner> NodeList;

		typedef std::unique_ptr<Subnode> SubnodeOwner;
		typedef std::vector<SubnodeOwner> SubnodeList;

		/// private members ///
		NodeList nodes;
		NetworkIdGenerator idGenerator;

	public:
		// type for the indexes of each node in the graph
		typedef uint16_t Index;

		Graph() {}
		Graph(const std::string& filename);

		void addEdge(Node::ID srcNode, Node::ID destNode);
		inline size_t nodeCount() const { return nodes.size(); }

		void print();

	private:

		inline Node* negNode(Node::ID netid) { return nodes[2 * netid].get(); }
		inline Node* posNode(Node::ID netid) { return nodes[2 * netid + 1].get(); }
	};

	inline Graph::Index index(const Subnode* node) {
		return (Graph::Index) (node->isNegative() ? 2 * node->getNetid() : 2 * node->getNetid() + 1);
	}

}


#endif //GRAPH_H
