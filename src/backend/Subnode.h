#ifndef SUBNODE_H
#define SUBNODE_H


#include <sstream>
#include "Node.h"

namespace Network {
	enum Polarity { Negative, Positive };

	class ResidualGraph;

	class Subnode : public Node {

		friend class ResidualGraph;

		/// private members ///
		Polarity polarity;

	public:

		inline const Polarity& getPolarity() const {
			return polarity;
		}

		inline bool isPositive() const {
			return getPolarity() == Polarity::Positive;
		}

		inline bool isNegative() const {
			return getPolarity() == Polarity::Negative;
		}

		inline virtual std::string toString() const {
			std::ostringstream stringStream;
			char sign = this->isNegative() ? '-' : '+';
			stringStream << "Node(" << this->getId() << ", " << sign << ")";
			return stringStream.str();
		}

	protected:
		// a node can only be created by friend classes or by subclasses
		Subnode(ID id, ID netid, Polarity polarity) : Node(id, netid), polarity(polarity) { }

	};

}


#endif //SUBNODE_H
