#include <iostream>
#include "Graph.h"
#include "Path.h"

namespace Network {

	/**
	 * Adds a new edge to the graph. An edge is considered to be two links with inverse directions, which means
	 * that the two nodes will be linked between each other.
	 * When a new edge is added the nodes are added to the graph as well if they didn't exist in the graph
	 * before.
	 * @param node1 id of one node of the edge
	 * @param node2 id of the other node of the edge
	 */
	void Graph::addEdge(Node::ID srcId, Node::ID destId) {
		Node::ID srcNetid = idGenerator.getNetid(srcId);
		Node::ID destNetid = idGenerator.getNetid(destId);

		if(srcNetid >= nodes.size()) {
			// source is a new node
			// create the node and add it to the nodes list
			nodes.push_back(std::unique_ptr<Node>(new Node(srcId, srcNetid)));
		}

		if(destNetid >= nodes.size()) {
			// destination is a new node
			// create the node and add it to the nodes list
			nodes.push_back(std::unique_ptr<Node>(new Node(destId, destNetid)));
		}

		// double link the nodes
		nodes[srcNetid]->addOutLink(nodes[destNetid].get());
		nodes[destNetid]->addOutLink(nodes[srcNetid].get());
	}

	void Graph::print() {
		using namespace std;

		cout << "Graph" << endl;
		for(auto& node : nodes) {
			if(node != nullptr) {
				cout << node->toString() << "[ ";

				for (auto& link : node->getOutLinks()) {
					cout << link << " ";
				}
				cout << "]" << endl;
			}
		}
	}

	unsigned int Graph::getConnectivityByNetid(Node::ID srcNetid, Node::ID destNetid) const {

		// get the residual graph from the current graph
		ResidualGraph residual(*this);
		residual.print();

		Link::Flow maxFlow = 0;
		Path path(residual, residual.subnodes[posIndex(srcNetid)].get(),
				  residual.subnodes[negIndex(destNetid)].get());

		while(residual.getPath(srcNetid, destNetid, path)) {

			Link::Flow pathMaxFlow = path.getFlow();
			path.adjustFlows(pathMaxFlow);

			maxFlow += pathMaxFlow;
		}

		return maxFlow;
	}
}
