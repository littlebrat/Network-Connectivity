#ifndef SUBNODE_H
#define SUBNODE_H


#include "Node.h"

namespace Network {
	enum Polarity { Negative, Positive };



	class Subnode : public Node {

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

	protected:
		// a node can only be created by friend classes or by subclasses
		Subnode(ID id, ID netid, Polarity polarity) : Node(id, netid), polarity(polarity) { }

	};

}


#endif //SUBNODE_H
