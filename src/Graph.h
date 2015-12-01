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
#include "Connectivity.h"

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

		inline Connectivity getConnectivity(Node::ID srcNode, Node::ID destNode) const {
			return getConnectivityByNetid(idGenerator.netid(srcNode), idGenerator.netid(destNode));
		}

		inline Connectivity getConnectivity() const {
			return getConnectivityByNetid();
		}

		typedef std::vector<unsigned> Distribuition;

		Distribuition getDistribuition() const;

	private:
		Connectivity getConnectivityByNetid(Node::ID srcNetid, Node::ID destNetid) const;

		Connectivity getConnectivityByNetid() const;

	};

}


#endif //GRAPH_H
