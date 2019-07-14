#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "base.hpp"

class Command : public Base {
	private:
		std::string argument;
		bool checkStatus;
	public:
		Command();
		Command(std::string);
		
		int spawn(char*, char**);
		bool execute(int, int);

		std::string getString();
};

#endif

