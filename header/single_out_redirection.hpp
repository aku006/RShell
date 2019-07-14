#ifndef __SINGLE_OUT_REDIRECTION_HPP__
#define __SINGLE_OUT_REDIRECTION_HPP__

#include "connector.hpp"

class SingleOutRedirection : public Connector {
	public:
		SingleOutRedirection();
		SingleOutRedirection(Base*, Base*);
		bool execute(int, int);
		std::string getString() { };
};

#endif
