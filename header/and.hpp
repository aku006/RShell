#ifndef __AND_HPP__
#define __AND_HPP__

#include "connector.hpp"

class And : public Connector {
	public:
		And();
		And(Base*, Base*);
		bool execute(int, int);
		std::string getString() { }
};

#endif //__AND_HPP__

