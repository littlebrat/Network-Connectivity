#include "Path.h"

Network::Path::Path(Network::Graph& graph, Network::Node* srcNode, Network::Node* destNode)
		: graph(graph)
		, srcNode(srcNode)
		, destNode(destNode)
		, parents(graph.nodes.size()) {

	reset();
}

/**
 * Returns the maxflow of the path. If the path is not valid the maxflow will be zero.
 */
Network::Link::Flow Network::Path::getMaxFlow() {

	Link::Flow maxFlow = UINT16_MAX;

	Node* node = destNode;
	Node* parent = parents[index(destNode)];

	while(parent != nullptr) {
		Link::Flow linkMaxFlow = parent->getOutLink(node)->getMaxFlow();

		if(linkMaxFlow < maxFlow) {
			maxFlow = linkMaxFlow;
		}

		// move to next link
		node = parent;
		parent = parents[index(node)];
	}

	return maxFlow;
}


void Network::Path::adjustFlows(Network::Link::Flow maxFlow) {
	Node* node = destNode;
	Node* parent = parents[index(destNode)];

	while(parent != nullptr) {
		Link* outLink = parent->getOutLink(node);
		Link* inLink = parent->getInLink(node);

		outLink->setMaxFlow(outLink->getMaxFlow() - maxFlow);
		inLink->setMaxFlow(inLink->getMaxFlow() + maxFlow);

		// move to next link
		node = parent;
		parent = parents[index(node)];
	}
}
