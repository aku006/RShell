#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "base.hpp"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <stack>
#include <queue>
#include <boost/tokenizer.hpp>

#include "../header/command.hpp"
#include "../unit_tests/mockCommand.hpp"
#include "../header/and.hpp"
#include "../header/base.hpp"
//#include "../header/connector.hpp"
#include "../header/or.hpp"
#include "../header/semicolon.hpp"

#include "../header/double_out_redirection.hpp"
#include "../header/input_redirection.hpp"
//#include "../header/pipe.hpp"
#include "../header/single_out_redirection.hpp"

//class Base;

class Parser {
	public:
		Parser();
		Parser(std::string);
		void execute(int, int);		
	private:
		std::vector<Base*> obj;
};

#endif
