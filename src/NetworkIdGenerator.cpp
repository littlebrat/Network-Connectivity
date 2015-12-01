#include "NetworkIdGenerator.h"


Network::Node::ID Network::NetworkIdGenerator::getNetid(Network::Node::ID id) {

    auto result = this->idMap.insert(std::make_pair(id, this->netidCount));
    if(result.second) {
        // the node was inserted which means it is a new node
        this->netidCount++;
    }

    // return the mapped value which is the node's network id
    return result.first->second;
    
}
