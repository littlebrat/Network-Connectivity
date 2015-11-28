#include <algorithm>
#include "Node.h"

namespace Network {

	Link* Node::getOutLink(Node* destNode) {
		for(auto it = outLinks.begin(); it != outLinks.end(); it++) {
			if(it->getDestNode() == destNode)
				return &(*it);
		}

		return nullptr;
	}


}
