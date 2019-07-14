#ifndef __FAKE_TRUE_COMMAND_HPP__
#define __FAKE_TRUE_COMMAND_HPP__

#include <iostream>
#include "../header/base.hpp"

/*A fake "command" that returns true, meant to test out connectors*/
class FakeTrueCommand : public Base {
	public:
		FakeTrueCommand() { };

		bool execute(int in, int out) {std::cout << "This is true." << std::endl; return true;}
		std::string getString() { }
};

#endif
