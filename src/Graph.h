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

namespace Network {

	class Graph {

		typedef std::unique_ptr<Node> NodeOwner;
		typedef std::array<NodeOwner, Node::MAX_ID + 1> NodeList;
		typedef std::unique_ptr<Link> LinkOwner;
		typedef std::array<LinkOwner, Node::MAX_ID + 1> LinkList;

		typedef std::unique_ptr<Subnode> SubnodeOwner;
		typedef std::array<SubnodeOwner, 2 * (Node::MAX_ID + 1)> SubnodeList;

		/// private members ///
		NodeList nodes;
		LinkList outLinks;

	public:
		// type for the indexes of each node in the graph
		typedef uint16_t Index;

		Graph();
		Graph(const std::string& filename);

		void addEdge(Node::ID srcNode, Node::ID destNode);
		inline size_t nodeCount() const { return nodes.size(); }

		inline void print() const {
			return print(Graph::nodes);
		}

	private:

		template <typename T, size_t N>
		void print(const std::array<T, N>& nodes) const;

		inline Node* negNode(Node::ID id) { return nodes[2 * id].get(); }
		inline Node* posNode(Node::ID id) { return nodes[2 * id + 1].get(); }
	};

	inline Graph::Index index(const Subnode* node) {
		return (Graph::Index) (node->isNegative() ? 2 * node->getNetid() : 2 * node->getNetid() + 1);
	}

}


#endif //GRAPH_H
