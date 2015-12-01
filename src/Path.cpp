#include "Path.h"

Network::Path::Path(Network::ResidualGraph &graph, Network::Subnode *srcSubnode, Network::Subnode *destSubnode) 
		: graph(graph)
		, srcSubnode(srcSubnode)
		, destSubnode(destSubnode)
		, parents(graph.subnodes.size()) {

	reset();
}

/**
 * Returns the maxflow of the path. If the path is not valid the maxflow will be zero.
 */
Network::Link::Flow Network::Path::getFlow() {

	Link::Flow flow = UINT16_MAX;

	Subnode* node = destSubnode;
	Subnode* parent = parents[index(destSubnode)];

	while(parent != nullptr) {
		Link::Flow linkFlow = parent->getOutLink(node)->getFlow();

		if(linkFlow < flow) {
			flow = linkFlow;
		}

		// move to next link
		node = parent;
		parent = parents[index(node)];
	}

	return flow;
}


void Network::Path::adjustFlows() {
	Subnode* node = destSubnode;
	Subnode* parent = parents[index(destSubnode)];

	while(parent != nullptr) {
		Link* outLink = parent->getOutLink(node);
		Link* inLink = parent->getInLink(node);

		outLink->setFlow((Link::Flow) (outLink->getFlow() - 1));
		inLink->setFlow((Link::Flow) (inLink->getFlow() + 1));

		// move to next link
		node = parent;
		parent = parents[index(node)];
	}
}
