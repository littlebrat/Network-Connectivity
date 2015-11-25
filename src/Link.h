#ifndef LINK_H
#define LINK_H

#include <cstdint>

namespace Network {

	class Node;

	class Link {

	public:
		// flows can only have 3 values 0, 1 and 2
		typedef uint16_t Flow;

		Link(Node* destNode, Flow maxFlow) : destNode(destNode), maxFlow(maxFlow) { }


		inline Node* getDestNode() const {
			return destNode;
		}

		inline void setDestNode(Node* destNode) {
			Link::destNode = destNode;
		}

		inline Flow getMaxFlow() const {
			return maxFlow;
		}

		inline void setMaxFlow(Flow maxFlow) {
			Link::maxFlow = maxFlow;
		}

	private:
		Node* destNode;  // destination node of the link
		Flow maxFlow;   // maximum flow that can go through this link
	};

	std::ostream& operator<<(std::ostream& out, const Link& link);

}


#endif //LINK_H
