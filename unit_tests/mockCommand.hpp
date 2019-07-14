#ifndef __MOCK_COMMAND_HPP__
#define __MOCK_COMMAND_HPP__

#include <iostream>
#include <string.h>
#include "../header/base.hpp"

/*A fake "command" that takes in a string, command class is incomplete atm*/
class mockCommand : public Base {
	private:
		std::string argList;
	public:
		mockCommand() { };
		mockCommand(std::string arg) {
			argList = arg;
		};
	
		std::string getArgs() {
			return argList;
		}	
		bool execute(int in, int out) {std::cout << "This is true." << std::endl; return true;}
		std::string getString() { }
};

#endif
