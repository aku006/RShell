#ifndef __INPUT_REDIRECTION_HPP__
#define __INPUT_REDIRECTION_HPP__

#include "connector.hpp"

class InputRedirection : public Connector {
	public:
		InputRedirection();
		InputRedirection(Base*, Base*);
		bool execute(int, int);
		std::string getString() { }
};

#endif

