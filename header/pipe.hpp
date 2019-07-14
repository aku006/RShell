#ifndef __PIPE_HPP__
#define __PIPE_HPP__

#include "connector.hpp"

class Pipe : public Connector {
	public:
		Pipe();
		Pipe(Base*, Base*);
		bool execute(int, int);
		std::string getString() { };
};

#endif

