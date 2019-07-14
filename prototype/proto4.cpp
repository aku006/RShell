#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <vector>

int main() {
	std::string input;
	char *conv;
	std::vector<char*> connector;
	std::vector<char*> command;
	std::cout << "enter command" << std::endl;
	getline(std::cin, input);
	//std::cout << input << std::endl;

	char baws[input.length() + 1];

	strcpy(baws, input.c_str());
	
	conv = strtok(baws, " ");
	while (conv) {
		std::cout << conv << std::endl;
		if( (conv != "&&") || (conv != "||") || (conv != ";")) {
			command.push_back(conv);
		}
		conv = strtok(NULL, " ");
	}

	return 0;
}
