#include <iostream>
#include "../src/Graph.h"

using namespace Network;


Graph simpleGraph() {
	Graph graph;

	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	graph.addEdge(2, 3);

	return graph;
}

int main() {

	Graph graph = simpleGraph();
	std::cout << graph << std::endl;

    return 0;
}