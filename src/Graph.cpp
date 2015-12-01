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

	unsigned Graph::getConnectivity() const {

		// get the residual graph from the current graph
		ResidualGraph residual(*this);
		residual.print();

		unsigned connectivity = 0;

		return connectivity;
	}


}

//unsigned Network::Graph::getConnectivity(Network::Node::ID srcNode, Network::Node::ID destNode) {
//
//	Link::Flow maxFlow = 0;
//	Path path(*this, posNode(srcNode).get(), negNode(destNode).get());
//
//	while(getPath(srcNode, destNode, path)) {
//
//		// print path
//		std::cout << path << std::endl;
//
//		Link::Flow pathMaxFlow = path.getMaxFlow();
//		path.adjustFlows(pathMaxFlow);
//
//		std::cout << *this << std::endl;
//
//		maxFlow += pathMaxFlow;
//	}
//
//	return maxFlow;
//}

//
//void Network::Graph::createSupernode(Node::ID nodeId) {
//
//	// create the negative node
//	negNode(nodeId).reset(new Node(nodeId, Node::Polarity::Negative));
//	// create the positive node
//	posNode(nodeId).reset(new Node(nodeId, Node::Polarity::Positive));
//
//	// add link between the negative to the positive node with flow = 1
//	negNode(nodeId)->addOutLink(posNode(nodeId).get(), 1);
//
//	// add link between from the positive to the negative with flow = 0
//	// this is advantageous when implementing the connectivity algorithm
//	posNode(nodeId)->addOutLink(negNode(nodeId).get(), 0);
//
//	nodeCount += 2;
//}

