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
	graph.print();

	unsigned connectivity = graph.getConnectivity(srcId, destId);
	std::cout << "connectivity(" << srcId << ", " << destId << "): " << connectivity << std::endl;

	if(!verbose)
		enableOutput();

	Graph::Distribuition distribuition = graph.getDistribuition();

	std::cout << "Distribuition" << std::endl;
	std::cout << distribuition.size() << std::endl;

	for(size_t connectivity = 0; connectivity < distribuition.size() - 1; connectivity++) {
		std::cout << "connectivity[" << connectivity << "]=" << distribuition[connectivity] << std::endl;
	}
	std::cout << "connectivity[INFINITY]=" << distribuition[distribuition.size() - 1] << std::endl;

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

void test3(bool verbose = false) {
	Graph graph;
	graph.addEdge(1, 2);
	graph.addEdge(1, 5);
	graph.addEdge(1, 6);
	graph.addEdge(2, 3);
	graph.addEdge(3, 5);
	graph.addEdge(3, 4);
	graph.addEdge(4, 6);

	test(graph, 1, 4, 3, 2, verbose);
}

bool verbose = true;

int main() {

	test1(verbose);
	test2(verbose);
	test3(verbose);

	return 0;
}