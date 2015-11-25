#ifndef NODE_H
#define NODE_H

#include <cstdint>

namespace Network {

	class Node {
		// allow the Graph class to access the Node constructor
		friend class Graph;

	public:
		typedef uint8_t ID;
		const static ID MAX_ID = 99;  // nodes have ids between 0-99

		enum Polarity { Negative, Positive };

		/*
		 * An IDException is thrown when an attempt to create a node with an ID value higher than the MAX_ID
		 */
		class IDException : public std::exception {
			virtual const char* what() const throw() {
				return "the maximum value for a node ID is 99";
			}
		};

		inline ID getId() const { return id; }
		inline ID getPosition() const { return polarity == Negative ? id : (ID) (id + 1); }

	private:

		// a node can only be created by the graph class
		Node(ID id, Polarity polarity) : id(id), polarity(polarity) {
			if(id > MAX_ID) {
				throw IDException();
			}
		}

		ID id;              // id of the node
		Polarity polarity;  // polarity of this node

	};

}


#endif //NODE_H
