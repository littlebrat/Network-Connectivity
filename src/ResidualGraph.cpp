#include <iostream>
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
        subnodes[posIndex(netid)]->addOutLink(subnodes[negIndex(netid)].get(), 0);
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

void Network::ResidualGraph::print() {
    using namespace std;

    cout << "Graph" << endl;
    for(auto& node : subnodes) {
        if(node != nullptr) {
            cout << node->toString() << "[ ";

            for (auto& link : node->getOutLinks()) {
                cout << link << " ";
            }
            cout << "]" << endl;
        }
    }
}

bool Network::ResidualGraph::getPath(Network::Node::ID srcNetid, Network::Node::ID destNetid,
                                     Network::Path &path, std::vector<bool>& visited) {

    /**
	 * The search is made from the positive source node to the negative destination node.
	 */
    bool found = false;

    std::queue<Subnode*> fringe;
    visited[negIndex(srcNetid)] = true;
    visited[posIndex(destNetid)] = true;

    // push outward node from the starting node to the queue.
    fringe.push(subnodes[posIndex(srcNetid)].get());

    while(!fringe.empty()) {

        Subnode* u = fringe.front();
        fringe.pop();
        visited[index(u)] = true;

        if(u == subnodes[negIndex(destNetid)].get()) {
            found = true;
            break;
        }

        // Add successors of u to the queue, if they have not been visited yet.
        for(auto& link : u->getOutLinks()) {

            // consider the links with flow 0 to not exist
            if(link.getFlow() > 0) {
                Subnode* v = (Subnode*) link.getOutNode();

                if (!visited[index(v)]) {
                    fringe.push(v);
                    path.setParent(v, u);
                }
            }
        }
    }

    return found;
}

void Network::ResidualGraph::getDisconnectedNodes(const std::vector<bool> &visited,
                                                  Network::Connectivity &connectivity) {

    // find super nodes where the negative node is visited and the positive node is not

    for(auto& node : subnodes) {

        if(!visited[index(node.get())]) {
            if(node->isPositive() && visited[negIndex(node->getNetid())]) {
                // this supernode is a disconnect node
                // store the id of the node
                connectivity.addDisconnectNode(node->getId());
            }
        }
    }
}
