#ifndef GRAPH_H
#define GRAPH_H

#include <cstdint>
#include <vector>
#include <string>

class Graph {

public:

    typedef uint8_t Node;               // nodes can only have ids from 0 to 100
    typedef uint8_t Flow;               // assumes flows can't be bigger than 255
    typedef std::vector<Link> LinkList;

    class Link {

    public:
        Link(Node destNode, Flow maxFlow) : destNode(destNode), maxFlow(maxFlow) {}


        Node getDestNode() const {
            return destNode;
        }

        void setDestNode(Node destNode) {
            Link::destNode = destNode;
        }

        Flow getMaxFlow() const {
            return maxFlow;
        }

        void setMaxFlow(Flow maxFlow) {
            Link::maxFlow = maxFlow;
        }

    private:
        Node destNode;  // destination node of the link
        Flow maxFlow;   // maximum flow that can go through this link

    };

	Graph();
	Graph(std::string filename);

	void addLink(Node srcNode, Node destNode);

private:
    LinkList links;

};


#endif //GRAPH_H
