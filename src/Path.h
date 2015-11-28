#ifndef PATH_H
#define PATH_H

#include "Graph.h"

namespace Network {

	class Path {

	public:

		/*
		 * An InvalidException is thrown when methods that need a valid path are called on an invalid path.
		 */
		class InvalidException : public std::exception {
			virtual const char* what() const throw() {
				return "this method can't be called when the path is invalid";
			}
		};

		explicit Path(Graph& graph, Node* srcNode, Node* destNode);

		inline Node* getSrcNode() const {
			return srcNode;
		}

		inline Node* getDestNode() const {
			return destNode;
		}

		Link::Flow getMaxFlow() const;

		inline bool isValid() const {
			return parents[graph.index(destNode)] != nullptr;
		}

		inline void setParent(Node* node, Node* parent) {
			parents[graph.index(node)] = parent;
		}

		void invertLinks();
		void reset();

	private:
		Graph& graph;               // graph where the path exists
		Node* srcNode;              // first node in the path
		Node* destNode;             // last node in the path
		std::vector<Node*> parents; // stores the parents of each node
		Link::Flow maxFlow;         // maximum flow that can go through this path

		/**
		 * The path is invalid if the destination node has no parent. So,to invalidate the path
		 * is necessary to clear the destination node parent.
		 */
		inline void invalidate() {
			parents[graph.index(destNode)] = nullptr;
		}
	};

}


#endif //PATH_H
