#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <vector>
#include <ostream>
#include "Link.h"

namespace Network {

	/**
	 * A supernode is composed by the negative node and a positive node linked from the negative
	 * to the positive. The negative node has only the in-links of the super node and the positive
	 * node has the out-links. For this reason each node must have a polarity property.
	 */

	class Node {

	public:
		typedef uint16_t ID;
		const static ID MAX_ID = 99;  // nodes have ids between 0-99
		typedef std::vector<Link> LinkList;

		enum Polarity { Negative, Positive };

		/*
		 * An IDException is thrown when an attempt to create a node with an ID value higher than the MAX_ID
		 */
		class IDException : public std::exception {
			virtual const char* what() const throw() {
				return "the maximum value for a node ID is 99";
			}
		};

	private:
		// allow the Graph class to access the Node constructor
		friend class Graph;

		// a node can only be created by friend classes
		Node(ID id, Polarity polarity) : id(id), polarity(polarity) {
			if(id > MAX_ID) {
				throw IDException();
			}
		}

	public: // public methods

		inline ID getId() const {
			return id;
		}
		
		inline const Polarity& getPolarity() const {
			return polarity;
		}

		inline void addOutLink(Node* destNode, Link::Flow maxFlow) {
			outLinks.push_back(Link(destNode, maxFlow));
		}

		inline const LinkList& getLinks() const {
			return outLinks;
		}

	private:
		ID id;              // id of the node
		Polarity polarity;  // polarity of this node
		LinkList outLinks;  // out links for this node in the graph

	};

	/*
	 * Allows that Node objects can be printed in the same form as other types.
	 * (e.g. std::cout << node << std::endl)
	 * Nodes are printed with only its id and polarity, the links are not printed.
	 */
	inline std::ostream& operator<<(std::ostream& out, const Node& node) {
		char polarity = node.getPolarity() == Node::Polarity::Negative ? '-' : '+';
		out << "Node(" << node.getId() << ", " << polarity << ")";
		return out;
	}

}


#endif //NODE_H
