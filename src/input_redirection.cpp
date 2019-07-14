#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../header/input_redirection.hpp"

InputRedirection::InputRedirection() : Connector() {}

InputRedirection::InputRedirection(Base* leftCommand, Base* rightCommand) : Connector(leftCommand, rightCommand) {}

bool InputRedirection::execute(int in, int out) {
	int fd = in;
	int ret = out;

	int x;
	int y;
	int z = dup(0);

	std::string arg = right->getString();
	
	x = open(arg.c_str(), O_RDONLY);

	if (x < 0) {
		perror("Input");
		return false;
	}

	y = dup2(x, 0);
	system(left->getString().c_str());
	
	z = dup2(z, 0);
	close(x);

	return true;
}		

