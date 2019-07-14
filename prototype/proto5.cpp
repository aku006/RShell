#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stack>
#include <vector>
#include <queue>
#include <string.h>
#include <boost/tokenizer.hpp>

void shuntingYard(std::vector<std::string> sauce, std::vector<std::string> dest) {
	
}
//using namespace boost;
int main() {
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(" ");
	std::string input;
	//std::stack<char*> inputs;
	std::stack<std::string> conn;
	std::stack<std::string> output;
	std::vector<std::string> conv;
	//char *conv;

	std::cout << "enter a command" << std::endl;
	std::getline(std::cin, input);
	
	tokenizer tok(input, sep);
	
	for(boost::tokenizer<boost::char_separator<char> >::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
		std::cout << *beg << std::endl;	
		conv.push_back(*beg);
	}

	//conv = strtok(baws, " ");
	if(conv.at(0) == "hey") {
		std::cout << "hello there" << std::endl;
	}
	for (unsigned i = 0; i < conv.size(); ++i) {
		//std::cout << conv.at(i) << std::endl;
		if (conv.at(i) == "#") {
			break;
		} else if (  (conv.at(i) == "||") || (conv.at(i) == "&&") || (conv.at(i) == ";") ) {
			//if connector
			//rn we're dealing with cases that only deal with 
			//two commands and a connector
			//thus our code will be written to accomodate such cases for now

			std::cout << "2: " << conv.at(i) << std::endl;
			/*if(conn.size() != 0) {:wq
 *
				while(conv != "&&" || conv != "||" || conv != ";") {
					output.push(conn.top());
					conn.pop();
				}
			}*/
			conn.push(conv.at(i));

		} else { 
			//if command, just "print"
			std::cout << "1: " << conv.at(i) << std::endl;
			output.push(conv.at(i));
		}
		/*if(conv == "(") {
			conn.push(conv);
		} else if ( conv == ")") {
			while(conn.top() != "(" ) {
				output.push(conn.top());
				conn.pop();
			}
			conn.pop();
		}*/ 
		//worry about parentheses much later
		//conv = strtok(NULL, " ");
	}
	
	/*while(conn.size() != 0) {
		output.push(conn.top());
		conn.pop();
	}*/
	//std::cout << "nyes" << std::endl;
	/*while(output.size() != 0) {
		std::cout << output.front() << " ";
		output.pop();
	}
	*/
	std::cout << std::endl;

	return 0;
}
