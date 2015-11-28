#ifndef PATH_H
#define PATH_H

#include "Graph.h"

namespace Network {

	class Path {

	public:

		explicit Path(Graph& graph, Node* srcNode, Node* destNode);

		inline Node* getSrcNode() const {
			return srcNode;
		}

		inline Node* getDestNode() const {
			return destNode;
		}

		Link::Flow getMaxFlow();

		inline bool isValid() const {
			return parents[index(destNode)] != nullptr;
		}

		inline void setParent(Node* node, Node* parent) {
			parents[index(node)] = parent;
		}

		void invertLinks();

		/**
		 * The path is invalid if the destination node has no parent. So,to invalidate the path
		 * is necessary to clear the destination node parent.
		 */
		inline void reset() {
			parents[index(srcNode)] = nullptr;
			parents[index(destNode)] = nullptr;
		}

	private:
		Graph& graph;               // graph where the path exists
		Node* srcNode;              // first node in the path
		Node* destNode;             // last node in the path
		std::vector<Node*> parents; // stores the parents of each node

	};

}


#endif //PATH_H
