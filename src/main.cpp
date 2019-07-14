#include <iostream>
#include <string>
#include "../header/base.hpp"
#include "../header/command.hpp"
#include "../header/connector.hpp"
#include "../header/and.hpp"
#include "../header/or.hpp"
#include "../header/semicolon.hpp"
#include "../header/parser.hpp"
/*
int main(int argc, char** argv) {
	std::string input;

	std::cout << "$ ";
	std::getline(std::cin, input);
	Parser* parseThis = new Parser(input);

	exec(root->execute()); //Dummy execute, should actually execute the executable at the end
}*/

int main() {
	std::string input;
	while(1) {
		int in = 0;
		int out = 1;
		std::cout << "$ ";
		getline(std::cin, input);
		//std::cout << std::endl;
		
		Parser *built = new Parser(input);
		built->execute(in, out);
	}
	return 0;
}


