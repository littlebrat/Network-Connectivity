#include "Path.h"

Network::Path::Path(Network::Graph& graph, Network::Node* srcNode, Network::Node* destNode)
		: graph(graph)
		, srcNode(srcNode)
		, destNode(destNode)
		, parents(graph.nodes.size()) {

	// ensure that the path is initialized invalid
	invalidate();
}
