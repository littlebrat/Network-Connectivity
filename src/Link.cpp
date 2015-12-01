#include <ostream>
#include "Link.h"
#include "Node.h"

namespace Network {
	std::ostream& operator<<(std::ostream& out, const Link& link) {
		out << "Link(" << *link.getOutNode() << ", " << link.getFlow() << ")";
		return out;
	}
}



