#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Path.h"

namespace Network {

	Graph::Graph(const std::string &filename) {
		std::ifstream inFile(filename, std::ifstream::in);

		if(!inFile.is_open()) {
			throw std::string("can't open input file");
		}

		uint16_t id1, id2;
		while(inFile >> id1 >> id2) {
			addEdge(id1, id2);
		}
	}

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

	Connectivity Graph::getConnectivityByNetid(Node::ID srcNetid, Node::ID destNetid) const {

		// check if the source and the destination are directly connected
		for(auto& link : nodes[srcNetid]->getOutLinks()) {
			if(destNetid == link.getOutNode()->getNetid()) {
				return Connectivity();
			}
		}

		// get the residual graph from the current graph
		ResidualGraph residual(*this);

		Link::Flow maxFlow = 0;
		Path path(residual, residual.subnodes[posIndex(srcNetid)].get(),
				  residual.subnodes[negIndex(destNetid)].get());

		// visited nodes all initialized with False.
		std::vector<bool> visited(residual.subnodes.size(), false);
		while(residual.getPath(srcNetid, destNetid, path, visited)) {
			path.adjustFlows();
			maxFlow += 1;

			visited.assign(visited.size(), false);
		}

		Connectivity connectivity(maxFlow);
		residual.getDisconnectedNodes(visited, connectivity);

		return connectivity;
	}

	Connectivity Graph::getConnectivityByNetid() const {

		Connectivity minConnectivity;

		for(Node::ID u = 0; u < nodes.size(); u++) {
			for(Node::ID v = (Node::ID) (u + 1); v < nodes.size(); v++) {

				Connectivity connectivity = getConnectivityByNetid(u, v);

				if(connectivity < minConnectivity) {
					minConnectivity = connectivity;
				}
			}
		}

		return minConnectivity;
	}

	Graph::Distribuition Graph::getDistribuition() const {

		Distribuition connectivities(nodes.size() + 1, 0);

		for(Index u = 0; u < nodes.size(); u++) {
			for(Index v = u + 1; v < nodes.size(); v++) {

				Connectivity connectivity = getConnectivityByNetid(u, v);

				if(connectivity.getValue() == Link::FLOW_INFINITY) {
					// store the infinity count in the extra spot of the connectivities
					connectivities[nodes.size()]++;
				} else {
					connectivities[connectivity.getValue()]++;
				}

			}
		}

		return connectivities;
	}
}
