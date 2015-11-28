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

		void adjustFlows(Link::Flow maxFlow);

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

		/*
		 * Allows Path objects to be printed in the same form as other types (e.g. cout << path << endl).
		 * It must be a friend method because it needs to access private members.
		 * Paths are printed in the following format: Path(destnode<-node<-srcnode)
		 */
		friend std::ostream& operator<<(std::ostream& out, const Path& path) {
			using namespace std;

			out << "Path(";

			Node* node = path.destNode;
			while(node != nullptr) {
				Node* parent = path.parents[index(node)];
				out << *node;
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
