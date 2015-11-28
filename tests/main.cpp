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

unsigned testConnectivity(Graph& graph, Node::ID srcId, Node::ID destId) {
	unsigned connectivity = graph.getConnectivity(srcId, destId);
	std::cout << "connectivity(" << srcId << ", " << destId << "): " << connectivity << std::endl;
	return connectivity;
}

void test1() {
	std::cout << "Test 1:" << std::endl;

	Graph graph = simpleGraph();
	std::cout << graph << std::endl;

	if(testConnectivity(graph, 0, 3) == 2)
		std::cout << "Test 1 OK" << std::endl;
	else
		std::cout << "Test 1 FAILED" << std::endl;
}

void test2() {
	std::cout << "Test 2:" << std::endl;

	Graph graph;
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	std::cout << graph << std::endl;

	if(testConnectivity(graph, 0, 3) == 2)
		std::cout << "Test 2 OK" << std::endl;
	else
		std::cout << "Test 2 FAILED" << std::endl;
}

int main() {

	test2();
	return 0;
}