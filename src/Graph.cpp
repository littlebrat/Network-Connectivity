#include "Graph.h"

Network::Graph::Graph() {
	// ensure that all positions store an empty node
	for(auto& node : nodes) {
		node = nullptr;
	}
}

void Network::Graph::addEdge(Network::Node::ID srcNode, Network::Node::ID destNode) {

	// a super node is composed by the negative node and a positive node linked from the negative to the positive
	// the negative node jas only the in-links of the super node and the positive node has the out-links

	// if each node is not already in the graph create a super node and added to the graph
	if(negNode(srcNode) == nullptr) {
		// create the negative node
		negNode(srcNode).reset(new Node(srcNode, Node::Polarity::Negative));
		// create the positive node
		posNode(srcNode).reset(new Node(srcNode, Node::Polarity::Positive));

		// add link between the nodes of the super node
		negNode(srcNode)->addLink(posNode(srcNode).get(), DEFAULT_FLOW);
	}

	if(negNode(destNode) == nullptr) {
		// create the negative node
		negNode(destNode).reset(new Node(destNode, Node::Polarity::Negative));
		// create the positive node
		posNode(destNode).reset(new Node(destNode, Node::Polarity::Positive));

		// add link between the nodes of the super node
		negNode(destNode)->addLink(posNode(destNode).get(), DEFAULT_FLOW);
	}

	// add an edge between the two super nodes
	posNode(srcNode)->addLink(negNode(destNode).get(), DEFAULT_FLOW);
	posNode(destNode)->addLink(negNode(srcNode).get(), DEFAULT_FLOW);

}


