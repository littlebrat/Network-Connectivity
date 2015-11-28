#include <iostream>
#include <fstream>
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

void disableOutput() {
	std::cout.setstate(std::ios_base::failbit);
}

void enableOutput() {
	std::cout.clear();
}

void test(Graph& graph, Node::ID srcId, Node::ID destId, unsigned testId, unsigned expected, bool verbose = false) {
	
	if(!verbose)
		disableOutput();

	std::cout << "Test " << testId << std::endl;
	std::cout << graph << std::endl;

	unsigned connectivity = graph.getConnectivity(srcId, destId);
	std::cout << "connectivity(" << srcId << ", " << destId << "): " << connectivity << std::endl;

	if(!verbose)
		enableOutput();

	if(connectivity == expected)
		std::cout << "Test " << testId << " OK" << std::endl;
	else
		std::cout << "Test " << testId << " FAILED" << std::endl;
}

void test1(bool verbose = false) {
	Graph graph = simpleGraph();
	test(graph, 0, 3, 1, 2, verbose);
}

void test2(bool verbose = false) {
	Graph graph;
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	graph.addEdge(2, 3);

	test(graph, 0, 3, 2, 2, verbose);
}

int main() {

	test1();
	test2();
	return 0;
}