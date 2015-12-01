#ifndef NETWORKIDGENERATOR_H
#define NETWORKIDGENERATOR_H


#include <unordered_map>
#include "Node.h"

namespace Network {

	class NetworkIdGenerator {

	public:
		NetworkIdGenerator() : netidCount(0) {}

		Node::ID getNetid(Node::ID id);
		inline Node::ID netid(Node::ID id) const {
			return idMap.at(id);
		}

	private:
		Node::ID netidCount;                          // counter to assign unique network ids in order
		std::unordered_map<Node::ID, Node::ID> idMap; // maps node ids to network ids

	};

}



#endif //NETWORKIDGENERATOR_H
