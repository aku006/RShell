#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/pipe.hpp"

Pipe::Pipe() {}

Pipe::Pipe(Base* leftCommand, Base* rightCommand) : Connector(leftCommand, rightCommand) {}

bool Pipe::execute(int in, int out) {
	int fds[2];

	pipe(fds);

	if (pipe(fds) < 0) {
		perror("Pipe");
		return false;
	}

	if (left->execute(in, fds[1]) == false) {
		std::cout << "left child failed" << std::endl;
		std::cout << fds[1] << std::endl;
		return false;
	}

	close(fds[1]);

	if (right->execute(fds[0], out) == false) {
		std::cout << "right child failed" << std::endl;
		std::cout << fds[0] << std::endl;
		return false;
	}

	close(fds[0]);

	return true;
}

