#ifndef RESIDUALGRAPH_H
#define RESIDUALGRAPH_H

#include <memory>
#include "Subnode.h"

namespace Network {

    class Graph;

    typedef uint16_t Index;

    class ResidualGraph {

        typedef std::unique_ptr<Subnode> SubnodeOwner;
        typedef std::vector<SubnodeOwner> SubnodeList;

        /// private members ///
        SubnodeList subnodes;

    public:
        // type for the indexes of each node in the graph
        typedef uint16_t Index;

        ResidualGraph(const Graph& graph);

    };

    static inline Index negIndex(Node::ID netid) {
        return (Index) (2 * netid);
    }

    static inline Index posIndex(Node::ID netid) {
        return (Index) (2 * netid + 1);
    }

}


#endif //RESIDUALGRAPH_H
