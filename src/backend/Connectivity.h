#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include "Node.h"

namespace Network {

    class Connectivity {

    public:
        Connectivity(unsigned connectivity = Link::FLOW_INFINITY) : connectivity(connectivity) {}

        Connectivity& operator =(const Connectivity& other) {
            connectivity = other.connectivity;
            disconnectNodes = other.disconnectNodes;
            return *this;
        }

        inline unsigned getValue() const {
            return connectivity;
        }

        inline void addDisconnectNode(Node::ID nodeId) {
            disconnectNodes.push_back(nodeId);
        }

        inline const std::vector<Node::ID> getDisconnectNodes() const {
            return disconnectNodes;
        }

        bool operator <(const Connectivity &other) const {
            return this->connectivity < other.connectivity;
        }

    private:
        unsigned connectivity;
        std::vector<Node::ID> disconnectNodes; // list with nodes that disconnect

    };

    inline std::ostream& operator<<(std::ostream& out, const Connectivity& c) {
        out << "(" << c.getValue() << ", [ ";
        for(auto& id : c.getDisconnectNodes()) {
            out << id << " ";
        }
        out << "])";
        return out;
    }
}

#endif //CONNECTIVITY_H
