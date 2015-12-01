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
#include "ResidualGraph.h"
#include "Path.h"

namespace Network {

	class Graph {

		friend class ResidualGraph;

		typedef std::unique_ptr<Node> NodeOwner;
		typedef std::vector<NodeOwner> NodeList;

		/// private members ///
		NodeList nodes;
		NetworkIdGenerator idGenerator;

	public:
		Graph() {}
		Graph(const std::string& filename);

		void addEdge(Node::ID srcNode, Node::ID destNode);
		inline size_t nodeCount() const { return nodes.size(); }
		void print();

		inline unsigned getConnectivity(Node::ID srcNode, Node::ID destNode) const {
			return getConnectivityByNetid(idGenerator.netid(srcNode), idGenerator.netid(destNode));
		}

	private:
		unsigned getConnectivityByNetid(Node::ID srcNetid, Node::ID destNetid) const;

	};

}


#endif //GRAPH_H
