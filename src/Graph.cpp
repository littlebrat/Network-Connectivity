#include "Graph.h"

Network::Graph::Graph() {
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
	}

	if(negNode(node2) == nullptr) {
		// create the negative node
		negNode(node2).reset(new Node(node2, Node::Polarity::Negative));
		// create the positive node
		posNode(node2).reset(new Node(node2, Node::Polarity::Positive));

		// add link between the nodes of the supernode
		negNode(node2)->addLink(posNode(node2).get(), DEFAULT_FLOW);
	}

	// add an edge between the two supernodes
	posNode(node1)->addLink(negNode(node2).get(), DEFAULT_FLOW);
	posNode(node2)->addLink(negNode(node1).get(), DEFAULT_FLOW);

}

Network::Node* Network::Graph::search_bfs(Network::Node::ID start_node, Network::Node::ID goal_node)
{
	// Initialize the fringe with a Queue data structure.
	std::queue<Node> fringe;

	// Parents of all the nodes in the graph.
	Node parent[size] = { NULL };

	// Visited nodes all initialized with False.
	int visited[size] = {};

	// Push outward node from the starting node to the queue.
	fringe.push(*posNode(start_node));

	while(!fringe.empty())
	{
		// Take out first node of the queue.
		Node u = fringe.front();
		fringe.pop();

		// Check if it is the goal node.
		if(u.id == goal_node && u.polarity == Node::Polarity::Negative)
		{
			return parent;
		}

		// Add successors of u to the queue, if they have not been visited yet.
		for(auto& uv : u.getLinks())
		{
			Node v = *uv.getDestNode();

			// Check if we have visited node v. THIS IS WRONG!!!!!!
			if(visited[v.id] == 0)
			{
				fringe.push(v);
			}
		}
	}
	return NULL;
}


