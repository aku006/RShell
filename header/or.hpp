#ifndef __OR_HPP__
#define __OR_HPP__

#include "connector.hpp"

class Or : public Connector {
        public:
		Or();
                Or(Base*, Base*);
                bool execute(int, int);
		std::string getString() { }
};

#endif //__OR_HPP__


