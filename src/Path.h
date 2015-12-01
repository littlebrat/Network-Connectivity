#ifndef PATH_H
#define PATH_H


#include "ResidualGraph.h"

namespace Network {

    class Path {

    public:

        explicit Path(ResidualGraph& graph, Subnode* srcSubnode, Subnode* destSubnode);

        inline Subnode* getSrcSubnode() const {
            return srcSubnode;
        }

        inline Subnode* getDestSubnode() const {
            return destSubnode;
        }

        Link::Flow getFlow();

        inline bool isValid() const {
            return parents[index(destSubnode)] != nullptr;
        }

        inline void setParent(Subnode* node, Subnode* parent) {
            parents[index(node)] = parent;
        }

        void adjustFlows();

        /**
         * The path is invalid if the destination node has no parent. So,to invalidate the path
         * is necessary to clear the destination node parent.
         */
        inline void reset() {
            parents[index(srcSubnode)] = nullptr;
            parents[index(destSubnode)] = nullptr;
        }

    private:
        ResidualGraph& graph;           // graph where the path exists
        Subnode* srcSubnode;            // first node in the path
        Subnode* destSubnode;           // last node in the path
        std::vector<Subnode*> parents;  // stores the parents of each node

        /*
         * Allows Path objects to be printed in the same form as other types (e.g. cout << path << endl).
         * It must be a friend method because it needs to access private members.
         * Paths are printed in the following format: Path(destnode<-node<-srcnode)
         */
        friend std::ostream& operator<<(std::ostream& out, const Path& path) {
            using namespace std;

            out << "Path(";

            Subnode* node = path.destSubnode;
            while(node != nullptr) {
                Subnode* parent = path.parents[index(node)];
                out << node->toString();
                if(parent != nullptr) {
                    out << "<-";
                }

                node = parent;
            }

            return out;
        }

    };

}

#endif //PATH_H
