#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//attempt to utilize both fork and execvp at the same time
//code based on sample code from text

pid_t spawn(char* prog, char** arg_list) {
	pid_t child_pid;

	child_pid = fork();

	if(child_pid != 0) {
		return child_pid;
		//parent process
	} else {
		execvp(prog, arg_list);
	//:q
		std::cout << "error" << std::endl;
		abort();
	}
}

int main() {
	pid_t child_pid;
	int child_stat;
	pid_t fork;	
	
	char *argv[] = {"ls", "-a", NULL};
	
	std::cout << "just before fork" << std::endl;
	
	//child_pid = fork(); //should instantiate two processes from here on,
			    //one with the og pid, the other with child id
	fork = spawn("ls", argv);
	waitpid(fork, &child_stat, WUNTRACED);
	if (WIFEXITED(child_stat)) {
		std::cout << "kid process exited normally with code " << WEXITSTATUS(child_stat) << std::endl;	
	} else {
		std::cout << "shit happened" << std::endl;
	}
	
	/*wait (&child_pid);
	if (WIFEEXITED(child_pid)) {
		std::cout << "child finished normally" << std::endl;
	} else {
		std::cout << "not" << std::endl;	
	}*/
	
	std::cout << "end of main process" << std::endl;
	return 0;
}


