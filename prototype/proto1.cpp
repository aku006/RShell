//this code was a sample code from the text "Advanced Linux Programming"
//although changes were made as the original sample code was written in C
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t child_pid;
	
	std::cout << "the main program process ID is " << getpid() << std::endl;
	
	child_pid = fork();
	std::cout << "fork indicator" << std::endl;	
	if (child_pid != 0) {
		std::cout << "this is the parent process with id " << getpid() << std::endl;
		std::cout << "the child process ID is " << child_pid << std::endl;
	} else {
		std::cout << "this is the child process, with id " << getpid() << std::endl;
	}

	return 0;
}
