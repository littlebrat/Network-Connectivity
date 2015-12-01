#ifndef RESIDUALGRAPH_H
#define RESIDUALGRAPH_H

#include <memory>
#include "Subnode.h"

namespace Network {

    class Graph;
    class Path;

    typedef uint16_t Index;

    class ResidualGraph {

        friend class Graph;
        friend class Path;

        typedef std::unique_ptr<Subnode> SubnodeOwner;
        typedef std::vector<SubnodeOwner> SubnodeList;

        /// private members ///
        SubnodeList subnodes;

    public:
        // type for the indexes of each node in the graph
        typedef uint16_t Index;

        ResidualGraph(const Graph& graph);

        bool getPath(Node::ID srcNetid, Node::ID destNetid, Path &path);

        void print();

    };

    static inline Index negIndex(Node::ID netid) {
        return (Index) (2 * netid);
    }

    static inline Index posIndex(Node::ID netid) {
        return (Index) (2 * netid + 1);
    }

    static inline Index index(const Subnode* node) {
        return node->isNegative() ? negIndex(node->getNetid()) : posIndex(node->getNetid());
    }

}


#endif //RESIDUALGRAPH_H
