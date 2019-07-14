#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include "connector.hpp"

class Semicolon : public Connector{
        public:
		Semicolon();
                Semicolon(Base*, Base*);
                bool execute(int, int);
		std::string getString() { }
};

#endif //__SEMICOLON_HPP__
