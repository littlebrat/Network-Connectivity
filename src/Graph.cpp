#include <iostream>
#include "Graph.h"

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
}



//void Network::Graph::addEdge(Network::Node::ID node1, Network::Node::ID node2) {
//
//	// every added node to the graph is considered to be a supernode.
//	// check the Node.h file for the definition of a supernode.
//
//	// if each node is not already in the graph create a supernode and added to the graph
//	if(negNode(node1) == nullptr) {
//		createSupernode(node1);
//	}
//
//	if(negNode(node2) == nullptr) {
//		createSupernode(node2);
//	}
//
//	// add an edge between the two supernodes with flow = 1
//	posNode(node1)->addOutLink(negNode(node2).get(), 1);
//	negNode(node2)->addOutLink(posNode(node1).get(), 0);
//	posNode(node2)->addOutLink(negNode(node1).get(), 1);
//	negNode(node1)->addOutLink(posNode(node2).get(), 0);
//
//}

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
///**
// * Returns a sequence of nodes that constitute a path from the source node to the destination
// * node. To build this bath it implements a Breath First Search algorithm. Which means that it
// * will return the path with the least links between the source and destination node.
// */
//bool Network::Graph::getPath(Node::ID srcNode, Node::ID destNode, Path& path) {
//
//	/**
//	 * The search is made from the positive source node to the negative destination node.
//	 */
//	bool found = false;
//
//	std::queue<Node*> fringe;
//	// visited nodes all initialized with False.
//	std::vector<bool> visited(nodes.size(), false);
//	visited[index(negNode(srcNode).get())] = true;
//	visited[index(posNode(destNode).get())] = true;
//
//	// push outward node from the starting node to the queue.
//	fringe.push(posNode(srcNode).get());
//
//	while(!fringe.empty()) {
//
//		Node* u = fringe.front();
//		fringe.pop();
//		visited[index(u)] = true;
//
//		if(u == negNode(destNode).get()) {
//			found = true;
//			break;
//		}
//
//		// Add successors of u to the queue, if they have not been visited yet.
//		for(auto& link : u->getLinks()) {
//
//			// consider the links with flow 0 to not exist
//			if(link.getMaxFlow() > 0) {
//				Node* v = link.getDestNode();
//
//				if (!visited[index(v)]) {
//					fringe.push(v);
//					path.setParent(v, u);
//				}
//			}
//		}
//	}
//
//	return found;
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

