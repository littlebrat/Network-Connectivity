#include "Graph.h"

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
	// a supernode is composed by the negative node and a positive node linked from the negative to the positive
	// the negative node jas only the in-links of the supernode and the positive node has the out-links

	// if each node is not already in the graph create a supernode and added to the graph
	if(negNode(node1) == nullptr) {
		// create the negative node
		negNode(node1).reset(new Node(node1, Node::Polarity::Negative));
		// create the positive node
		posNode(node1).reset(new Node(node1, Node::Polarity::Positive));

		// add link between the nodes of the supernode
		negNode(node1)->addLink(posNode(node1).get(), DEFAULT_FLOW);

		nodeCount += 2;
	}

	if(negNode(node2) == nullptr) {
		// create the negative node
		negNode(node2).reset(new Node(node2, Node::Polarity::Negative));
		// create the positive node
		posNode(node2).reset(new Node(node2, Node::Polarity::Positive));

		// add link between the nodes of the supernode
		negNode(node2)->addLink(posNode(node2).get(), DEFAULT_FLOW);

		nodeCount += 2;
	}

	// add an edge between the two supernodes
	posNode(node1)->addLink(negNode(node2).get(), DEFAULT_FLOW);
	posNode(node2)->addLink(negNode(node1).get(), DEFAULT_FLOW);

}

/**
 * Returns a sequence of nodes that constitute a path from the source node to the destination
 * node. To build this bath it implements a Breath First Search algorithm. Which means that it
 * will return the path with the least links between the source and destination node.
 */
bool Network::Graph::getPath(Node::ID srcNode, Node::ID destNode, std::vector<Node*>& parents) {

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

			Node* v = link.getDestNode();

			if(!visited[index(v)]) {
				fringe.push(v);
				parents[index(v)] = u;
			}
		}
	}

	return found;
}

