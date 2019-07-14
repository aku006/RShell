#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

//playing around with execvp
//apparently, execvp does not take in a string for the executable ie "ls"
////but it also needs a c-array for its second input
////also noted in textbook mentioned in proto1.cpp
//warning of compilation warnings != cannot run file
int main() {
	char* argv[] = {"echo", "hello there",  NULL };
	execvp(argv[0],argv);
	std::cout << "hey baws" << std::endl;
	return 0;
}
