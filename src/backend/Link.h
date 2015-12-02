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

	public: // public types
		// flows can only have 3 values 0, 1 and 2
		typedef uint16_t Flow;
		static const Flow FLOW_INFINITY = UINT16_MAX;

	private:
		/// private members ///
		Node* outNode;  // out node of the link
		Flow flow;      // maximum flow that can go through this link

	public:

		Link(Node* outNode, Flow flow = FLOW_INFINITY) : outNode(outNode), flow(flow) { }

		inline Node* getOutNode() const {
			return outNode;
		}

		inline Flow getFlow() const {
			return flow;
		}

		inline void setFlow(Flow flow) {
			Link::flow = flow;
		}

	};

	/*
	 * Allows that Link objects can be printed in the same form as other types.
	 * (e.g. std::cout << link << std::endl)
	 * It must be implemented in the source to avoid the conflict of including Node.h in this header file.
	 */
	std::ostream& operator<<(std::ostream& out, const Link& link);

}


#endif //LINK_H
