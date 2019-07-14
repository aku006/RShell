#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <time.h>
#include "../header/command.hpp"

Command::Command() {
	this->argument = "";
	this->checkStatus = false;
}

Command::Command(std::string thisCommand) {
	this->argument = thisCommand;
	this->checkStatus = false;
}

/*Returns a true or false value, depending on whether the commmand ran properly or not*/
bool Command::execute(int in, int out) {
	//Values needed for execvp and fork
	pid_t child_pid;
	int child_status;
	pid_t forkThis;
	//NOTE: command class maybe taking an string that added a SPACE at the end
	std::string s = argument;//store member inside a temp var 's'
	int size = s.size();
	int index = 0;
	int numWords = 0;
	
	std::string echoArgs = "";
	std::string temp = ""; //Temporary string
	//std::cout << "command inital s " << s << std::endl;
	//if command has quotation amrks
	//Get the number of arguments
	for (int x = 0; x < size; x++) {
		if (s.at(x) == ' ') {
			numWords = numWords + 1;
		}
	}
	//Need to increment this once more since numWords will be one less
	numWords = numWords + 1;
	bool exitFlag = false;
	char* argList[numWords];

	bool testFlag = false; //Checks to see if test is a command entered
	bool bracketFlag = false;
	
	for (int i = 0; i < size; i++) {
		//If char at i is whitespace, create char array out of temp and push it onto char**
		//std::cout << temp << std::endl;
		//std::cout << i << std::endl;
		if(temp == "exit" && (i < 5)) {//very first thing has to be exit
			exitFlag = true;
		}
		
		//If test is entered, set the flag
		if (temp == "test" && (i < 5)) {
			testFlag = true;
		}

		//If [ is entered, set test flag
		if (temp == "[" && (i < 2)) {
			bracketFlag = true;
		//	testFlag = true;
		}

		if(temp == "]" && bracketFlag) {
			testFlag = true;
		}
		if (s.at(i) == ' ') { //if s.at(i) is about to enter another word, push tempt into index of args list
			argList[index] = new char [temp.length() + 1];
			std::strcpy(argList[index], temp.c_str());

			index = index + 1;
			temp = "";
		} else if (s.at(i) == '\"') {//if s.at(i) is a quote
			int x;
			//std::cout << "quote entered " << std::endl;
			for (x = i; s.at(x) != '\"'; ++x) {
				if(s.at(x) == ' ') {
					//std::cout << "quote-space entered" << std::endl;
					argList[index] = new char [temp.length() + 1];
					std::strcpy(argList[index], echoArgs.c_str());
					++index;
					echoArgs = "";
				} else {
					echoArgs += s.at(x);
				}
			}
			//adds last word
			argList[index] = new char [temp.length() + 1];
			std::strcpy(argList[index], echoArgs.c_str());
			echoArgs = "";

			i = x;
		}
		//Else just append char into temp
		else {
			temp += s.at(i);
		}
	}
	argList[index] = NULL; //Last index is empty, need to add NULL here
	/* for(int i = 0; i < numWords; ++i) {
		if(argList[i] == NULL) {
			std::cout << i << ": NULL" << std::endl;
			break;
		}
		std::cout << i << ": \"" << argList[i] << "\"" << std::endl;
	} 
	std::cout << numWords << std::endl; */
	
	if(exitFlag) {
		exit(1);
	}
		//Test function
	else if (testFlag) {
		//**NOTE**: tests require some type of tag to indicate whether its a file or dir
		//a word alone returns true
		//case for "test -e"
		//std::cout << "entered test" << std::endl;
		if (strcmp(argList[1], "-e") == 0) {
			struct stat buf;
			stat(argList[2], &buf);
			if (S_ISREG(buf.st_mode)) {
				std::cout << "(True)" << std::endl;
				return true;
			} else if (S_ISDIR(buf.st_mode)){
				std::cout << "(True)" << std::endl;
				return true;
			}
			else {
				std::cout << "(False)" << std::endl;
				return false;
			}
		}
		
		else if (strcmp(argList[1], "-f") == 0) {
			struct stat buf;

			stat(argList[2], &buf);
			if (S_ISREG(buf.st_mode)) {
				std::cout << "(True)" << std::endl;
				return true;
			}
			else {
				std::cout << "(False)" << std::endl;
				return false;
			}
		}

		else if (strcmp(argList[1], "-d") == 0) {
			//std::cout << "-d" << std::endl;
			struct stat buf;

			stat(argList[2], &buf);
			if (S_ISDIR(buf.st_mode)) {
				std::cout << "(True)" << std::endl;
				return true;
			}
			else {
				std::cout << "(False)" << std::endl;
				return false;
			}
		}
		else { //no test tag? -e
			struct stat buf;
			stat(argList[1], &buf); //assuming that the command only has 'test input'
			if (S_ISREG(buf.st_mode)) {
				std::cout << "(True)" << std::endl;
				return true;
			} else if (S_ISDIR(buf.st_mode)){
				std::cout << "(True)" << std::endl;
				return true;
			}
			else {
				std::cout << "(False)" << std::endl;
				return false;
			}
		}
	}

	else {
		
		//Pass arguments up to spawn
		//spawn(*argList, argList);
		child_pid = fork();

		//child process
		if (child_pid == 0) {
			if (execvp(argList[0], argList) == -1) {
				perror("Failed to execute");
				exit(99);
			}
			
			if (dup2(in, 0) < 0) {
				perror("Dup2 read");
				exit(99);
			}
			
			if (dup2(out, 1) < 0) {
				perror("Dupe2 write");
				exit(99);
			}
		}
	
		//parent process
		else if (child_pid > 0) {
			if((forkThis = wait(&child_status)) < 0) {
				perror("Parent failed to wait."); //Safeguard in case parent tries to run
				exit(1);
			}
		}
	
		else {
			perror("Fork failed.");
			exit(1);
		}
	
		forkThis = waitpid(child_pid, &child_status, WUNTRACED);
		//std::cout << WEXITSTATUS(child_status) << std::endl;
		//IF child_status is 99, then that means that this command failed
		if (WEXITSTATUS(child_status) != 0) {
			return false;
		}
		//Otherwise it worked
		else {
			return true;
		}
	}
}

std::string Command::getString() {
	return argument;
}

