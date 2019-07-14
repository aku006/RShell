#ifndef __FAKE_FALSE_COMMAND_HPP__
#define __FAKE_FALSE_COMMAND_HPP__

#include <iostream>
#include "../header/base.hpp"

/*A fake "command" that returns true, meant to test out connectors*/
class FakeFalseCommand : public Base {
        public:
                FakeFalseCommand() { };

                bool execute(int in, int out) {std::cout << "This is false." << std::endl; return false;}

		std::string getString() { }
};

#endif

