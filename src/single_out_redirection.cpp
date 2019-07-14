#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../header/single_out_redirection.hpp"

SingleOutRedirection::SingleOutRedirection() {}

SingleOutRedirection::SingleOutRedirection(Base* leftCommand, Base* rightCommand) : Connector(leftCommand, rightCommand) {}

bool SingleOutRedirection::execute(int in, int out) {
	int fd = in;
	int ret = out;

	int x;
	int y;
	int z = dup(1);
	std::string arg = right->getString();
	//std::cout << arg << std::endl;
	x = open(arg.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	//std::cout << arg << std::endl;
	//std::cout << ret << std::endl;

	if (x < 0) {
		perror("singleout-open");
		return false;
		//exit(1);
	}

	y = dup2(x,1);
	//std::cout << "yeetle" << std::endl;
	system(left->getString().c_str());	
	//int len = arg.size();
	//write(ret, arg, len);
	//bool result = left->execute(x, 1);


	z = dup2(z, 1);
	close(x);

	return true;
}

