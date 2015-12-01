#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <vector>
#include <ostream>

namespace Network {

	/**
	 * A supernode is composed by the negative node and a positive node linked from the negative
	 * to the positive. The negative node has only the in-links of the super node and the positive
	 * node has the out-links. For this reason each node must have a polarity property.
	 */

	class Node {

	public: // types
		typedef uint16_t ID;
		const static ID MAX_ID = 99;  // nodes have ids between 0-99

	private:
		/// private members ///
		ID id;      // id of the node
		ID netid;   // network id of the node

		/// friend classes ///
		// allow the Graph class to access the Node constructor
		friend class Graph;

	public: // public methods

		inline ID getId() const {
			return id;
		}

		inline ID getNetid() const {
			return netid;
		}

	protected:
		// a node can only be created by friend classes or by subclasses
		Node(ID id, ID netid) : id(id), netid(netid) { }

	};

	/*
	 * Allows that Node objects can be printed in the same form as other types.
	 * (e.g. std::cout << node << std::endl)
	 */
	inline std::ostream& operator<<(std::ostream& out, const Node& node) {
		return out << "Node(" << node.getId() << ")";
	}

}


#endif //NODE_H
