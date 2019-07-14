#ifndef __DOUBLE_OUT_REDIRECTION_HPP__
#define __DOUBLE_OUT_REDIRECTION_HPP__

#include "connector.hpp"

class DoubleOutRedirection : public Connector {
	public:
		DoubleOutRedirection();
		DoubleOutRedirection(Base*, Base*);
		bool execute(int, int);
		std::string getString() { };
};

#endif

