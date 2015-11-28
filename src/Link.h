#ifndef LINK_H
#define LINK_H

#include <cstdint>

namespace Network {

	class Node;

	/**
	 * A link is considered to be directed and only stores the destination node and the max flow
	 * of that link. This class must be used only in the Network namespace.
	 */
	class Link {

	public:
		// flows can only have 3 values 0, 1 and 2
		typedef uint16_t Flow;

		Link(Node* destNode, Flow maxFlow) : destNode(destNode), maxFlow(maxFlow) { }

		inline Node* getDestNode() const {
			return destNode;
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

	/*
	 * Allows that Link objects can be printed in the same form as other types.
	 * (e.g. std::cout << link << std::endl)
	 * It must be implemented in the source to avoid the conflict of including Node.h in this header file.
	 */
	std::ostream& operator<<(std::ostream& out, const Link& link);

}


#endif //LINK_H
