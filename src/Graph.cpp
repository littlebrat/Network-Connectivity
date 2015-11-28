#include "Graph.h"
#include "Path.h"

Network::Graph::Graph() : nodeCount(0) {
	// ensure that all positions store an empty node
	for(auto& node : nodes) {
		node = nullptr;
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
void Network::Graph::addEdge(Network::Node::ID node1, Network::Node::ID node2) {

	// every added node to the graph is considered to be a supernode.
	// check the Node.h file for the definition of a supernode.

	// if each node is not already in the graph create a supernode and added to the graph
	if(negNode(node1) == nullptr) {
		createSupernode(node1);
	}

	if(negNode(node2) == nullptr) {
		createSupernode(node1);
	}

	// add an edge between the two supernodes with flow = 1
	posNode(node1)->addOutLink(negNode(node2).get(), 1);
	posNode(node2)->addOutLink(negNode(node1).get(), 1);

}

unsigned Network::Graph::getConnectivity(Network::Node::ID srcNode, Network::Node::ID destNode) {

	Link::Flow maxFlow = 0;
	Path path(*this, posNode(srcNode).get(), negNode(destNode).get());

	while(getPath(srcNode, destNode, path)) {
		Link::Flow pathMaxFlow = path.getMaxFlow();
		path.adjustFlows(pathMaxFlow);
		maxFlow += pathMaxFlow;
	}

	return maxFlow;
}

/**
 * Returns a sequence of nodes that constitute a path from the source node to the destination
 * node. To build this bath it implements a Breath First Search algorithm. Which means that it
 * will return the path with the least links between the source and destination node.
 */
bool Network::Graph::getPath(Node::ID srcNode, Node::ID destNode, Path& path) {

	/**
	 * The search is made from the positive source node to the negative destination node.
	 */
	bool found = false;

	std::queue<Node*> fringe;
	// visited nodes all initialized with False.
	std::vector<bool> visited(nodes.size(), false);
	visited[index(negNode(srcNode).get())] = true;
	visited[index(posNode(destNode).get())] = true;

	// push outward node from the starting node to the queue.
	fringe.push(posNode(srcNode).get());

	while(!fringe.empty()) {

		Node* u = fringe.front();
		fringe.pop();
		visited[index(u)] = true;

		if(u == negNode(destNode).get()) {
			found = true;
			break;
		}

		// Add successors of u to the queue, if they have not been visited yet.
		for(auto& link : u->getLinks()) {
			
			// consider the links with flow 0 to not exist
			if(link.getMaxFlow() > 0) {
				Node* v = link.getDestNode();

				if (!visited[index(v)]) {
					fringe.push(v);
					path.setParent(v, u);
				}
			}
		}
	}

	return found;
}

void Network::Graph::createSupernode(Node::ID nodeId) {

	// create the negative node
	negNode(nodeId).reset(new Node(nodeId, Node::Polarity::Negative));
	// create the positive node
	posNode(nodeId).reset(new Node(nodeId, Node::Polarity::Positive));

	// add link between the negative to the positive node with flow = 1
	negNode(nodeId)->addOutLink(posNode(nodeId).get(), 1);

	// add link between from the positive to the negative with flow = 0
	// this is advantageous when implementing the connectivity algorithm
	posNode(nodeId)->addOutLink(negNode(nodeId).get(), 0);

	nodeCount += 2;
}
