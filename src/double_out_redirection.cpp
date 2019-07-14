#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../header/double_out_redirection.hpp"

DoubleOutRedirection::DoubleOutRedirection() {}

DoubleOutRedirection::DoubleOutRedirection(Base* leftCommand, Base* rightCommand) : Connector(leftCommand, rightCommand) {}

bool DoubleOutRedirection::execute(int in, int out) {
	int fd = in;
	int ret = out;
	
	int x;
	int y;
	int z = dup(1);
	
	std::string arg = right->getString();

	x = open(arg.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	
	if (x < 0) {
		perror("Append");
		return false;
	}

	y = dup2(x, 1);
	system(left->getString().c_str());
	
	z = dup2(z, 1);
	close(x);

	return true;
}

