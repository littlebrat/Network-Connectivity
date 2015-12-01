#include "ResidualGraph.h"
#include "Graph.h"

Network::ResidualGraph::ResidualGraph(const Network::Graph &graph) {

    // apply vertex splitting to each node in the graph
    for(const auto& node : graph.nodes) {
        subnodes.push_back(std::unique_ptr<Subnode>(new Subnode(node->getId(), node->getNetid(),
                                                                Polarity::Negative)));
        subnodes.push_back(std::unique_ptr<Subnode>(new Subnode(node->getId(), node->getNetid(),
                                                                Polarity::Positive)));

        Node::ID netid = node->getNetid();
        // link between the two subnodes
        // add link from the negative node to the positive node with unitary flow
        subnodes[negIndex(netid)]->addOutLink(subnodes[posIndex(netid)].get(), 1);
        // add link from the negative node to the positive node with flow zero
        subnodes[posIndex(netid)]->addOutLink(subnodes[negIndex(netid)].get(), 1);
    }

    // link between all the supernodes
    for(const auto& node : graph.nodes) {
        for(const auto& link : node->getOutLinks()) {
            Node::ID srcNetid = node->getNetid();
            Node::ID destNetid = link.getOutNode()->getNetid();

            // supernodes are connected by links with infinite flow from the positive subnode of the source
            // supernode to the negative subnode of the destination supernode

            subnodes[posIndex(srcNetid)]->addOutLink(subnodes[negIndex(destNetid)].get());

            // add a link with flow zero in the inverse direction
            subnodes[negIndex(destNetid)]->addOutLink(subnodes[posIndex(srcNetid)].get(), 0);
        }
    }
}
