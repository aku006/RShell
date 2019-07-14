# CS 100 Programming Project
Luccas Chang(862013904)

Alex Ku(862038874) 

### Intro:
As stated in the intro of assignment two, our goal is to create a command shell called rshell that can take user inputs comprising of commands and connectors. The project should be able to take in these commands (mainly bash commands) and connectors and, based on the connectors, parse the commands to be executed in an orderly and prioritized manner.

### Diagram:
![UML](https://github.com/cs100/spring_2019_assignment_assn1_luke_and_alex/blob/master/images/RShell%20UML-assn4.1.png?raw=true)

### Classes:
* class Base: This is the base class that all of our other classes will use. It includes the following data:
  * Data members: Base()
  * Functions: bool execute()
* class Command : public Base: This class builds an object by taking in a command and its following arguments. It inherits the bool execute() from the Base class, and will return either true or false. It runs execvp(), fork(), and waitpid() to determine whether the particular command returns true or not. In addition, it checks to see if the command is "exit", and if it is, it will exit the shell. The command also has a special case if either "test" is entered or if the argument is enclosed in brackets. Using an additional flag (-e, -d, or -f) and stat(), this class will see if the file passed into the argument both exists and is a certain type of file (regular or directory), and return true or false. Bool execute() now takes in two ints as parameters.
* class Connector : public Base: A Composite class that serves as an indicator to how the immediate commands (left and right of the connector). It inherits the execute() command from Base, and also contains a constructor with two pointers, which connects it to two different Command objects. It also serves as a base for its children (the specific instances &&, ||, or ;).
  * class And : public Connector: A subclass of Connector that runs the right-hand command only if the command on the left was executed correctly. When it is executed, it will return true only if both of its commands return true.
  * class Semicolon : public Connector: The semicolon subclass is to execute both left and right-handed commands without question. When it is executed, it will run the left Command, then return the truth value of the right Command.
  * class Or : public Connector: This subclass runs the right command only if the left command doesn't run. It returns true if either one of the commands runs, and false if both of them return false.
  * class DoubleOutRedirection : public Connector: Also a subclass of the connector, this class's purpose is to read an input, be it a command like "echo", and then append it to another file. The class should not overwrite the destination file's content.
  * class InputRedirection : public Connector: The goal of this class is to take in the contents of a file and transfer it to another destination. Emphasis on changing fd(0).
  * class SingleOutRedirection : public Connector: Similar to DoubleOutRedirection with the difference in that it creates and/or overwrites the destination file. Emphasizes working with fd(1) or the output.
  * class Pipe : public Connector: This forks a given process to run a command. A pipe is created, and the child process writes to one end of the pipe. Then the parent takes in the information written to the pipe via the child process's and writes said information to the specified destination.
* class Parser : public Base: This class tokenizes the input string which will then be itereated through to create a command or connect object depending on the token read. These objects will be pushed onto specified list to be retrieved again if the parser were to build a connector object. The case where the user inputs only one command is addressed outside of the loop. The class also takes into account whether executables are in parentheses or not, which affects the order of execution.
* The Hash and Exit classes were removed as the cases involving them were able to be addressed under the parser class.

### Research/prototype:
Initial research and testing around fork and execvp offered insight into how the two syscalls worked. In addition, further research from other texts provided further clarification on how these system calls work and how they can work together. The sycall waitpid definitely requires more research. But the current things we have learned from prototyping and research indicates that a fork splits a program into two identical pathways that can utilize its pid to perfrom differing operations. The execvp is a function that receives and executes core bash commands and essentially "breaks" from the program from which it was called on, although we are still uncertain as to how or whether the execvp can return to the program it was called on. Perhaps this is when waitpid is of use. We also learned that execvp also receives arguments that a command may utilize to execute a specific command.
This information can allow us to better understand how to create our "instance" tree through the parsing class, and how to execute said commands. Knowing how to parse the user inputs into a structure that can be fed and executed in an efficient and orderly manner will require further research. Although our understanding of the expression tree from cs14 and lab 3 from this course will give us a foundation to build on.

### Roadmap:
1. Creation of base class [Base Issue](https://github.com/cs100/spring_2019_assignment_assn1_luke_and_alex/issues/1#issue-437999319)
1. Creation of child classes (connector, command, and parsing)
1. Implementation of the parsing class [Parse Issue](https://github.com/cs100/spring_2019_assignment_assn1_luke_and_alex/issues/2#issue-437999469)
   1. Sorting command input into a container
   1. Separating the container into two other containers based on type (connectors vs. command)
   1. Test parsing of “echo hello; echo bye”
1. Implementation of the connector class [Connector](https://github.com/cs100/spring_2019_assignment_assn1_luke_and_alex/issues/3#issue-437999553)
   1. Evaluation of command line and whether each relevant command succeeds or not
   1. Execution of the particular connector based on the command
   1. Test “a ; b && c || d” to make sure the connectors works properly
1. Implementation of the command class [Command](https://github.com/cs100/spring_2019_assignment_assn1_luke_and_alex/issues/4#issue-437999646)
   1. Analysis of executable (“echo”, “ls”, etc.)
   1. Analysis of argument (ex. The “hello” part of the command “echo hello”)
   1. Execution of the command as a whole
   1. Test “echo hello” to make sure “hello” is properly output
1. Integration test [Unit Test](https://github.com/cs100/spring_2019_assignment_assn1_luke_and_alex/issues/5#issue-437999724)
   1. Test this full command line: “echo hello ; echo now && echo bye”
1. Implementation of test executable command
   1. Analysis of "test" and a pair of brackets
   1. Analysis of flags "-e", "-f", and "-d" in an argument
   1. Execution of both test and brackets to run the same command
   1. Test all these in rshell
      1. Test "test -e CMakeLists.txt" and "[ -e CMakeLists.txt ]" to make sure both return true
      1. Test "test -e c.txt" in both literal and bracket form to make sure both return false
      1. Also run -d and -f flags with these commands respectively in
      1. For -d, make sure it can find src/
1. Implementation of parentheses
   1. Analysis of parentheses
   1. Proper execution of executables in paren/theses with those not in parentheses
   1. Test "(echo a && echo b) || (echo c && echo d)" to make sure it runs properly. Should output a and b.
   1. Test "(echo a || echo b) && (echo c || echo d)" to make sure it properly outputs a and c.
1. Implementation of input redirection
   1. Analysis of "<" to execute input redirection to read from a file
   1. Execution of this connector to run with two commands
   1. Test "cat < input_red.txt" to make sure it returns true for a file that exists
   1. Test "cat < nonexist.txt" to make sure it returns false for a file that does not exist
1. Implementation of output redirection
   1. Analysis of ">" to execute output redirection to write to a file
   1. Analysis of ">>" to append output to a file
   1. Test if both create a file that does not exist
   1. Execute to make sure it can run
   1. Test "echo hello > out_red.txt" to make sure it can:
      1. Write "hello" to a text file
      1. Create out_red.txt if it does not exist
   1. Test "echo If you see this, that means that append is working. Probably. >> append_test.txt" to make sure it can:
      1. Append this string to append_test.txt instead of just overwriting the contents of the file.
      1. Create append_test.txt if it does not exist.
1. Implementation of pipe
   1. Analysis of "|" to run pipe
   1. Test "ls -la" | grep -e -r" to test if pipe works

### Alexander Ku - Updates For Assignment 3 (5/26/2019):
* Fixed quotations and hash issues from Assignment 2
* Added test command functionality to our Command class
  * Makes use of stat(), IS_DIR, and IS_REG to return true or false
  * Takes in a flag set by the argument: -e, -f, or -d
    * -e flag: Returns true if the file, whether it is a regular file or directory, exists.
    * -f flag: Returns true if the file exists and happens to be a regular file
    * -d flag: Returns true if the file exists and happens to be a directory
    * No flag: Run -e flag by default
  * Activates through two ways: if the word "test" is entered, or if the argument is enclosed in brackets
  * If only one bracket is entered, then run it into execvp() and make it fail there
* Added parentheses functionality to Parser class
  * If parentheses is found, parse connectors between them into a different vector
  * Also allows use of parentheses within parentheses
* Note: We did not add any new functions or classes. All we did was extend the functionality of existing functions in the classes we already had. Therefore, there are no changes in the UML.

### Alexander Ku - Updates for Assignment 4 (6/9/2019)
* Added a getString() function that returns the string of an object
  * Used for the sake of the input/output redirections
* Edited execute() in Command class to take in two ints as parameters
* Added dup2() in execute() for commands used by Pipe
* Added InputRedirection, SingleOutRedirection, and DoubleOutRedirection as Connector classes
  * Makes use of dup() and dup2() within the class itself
  * Opens the file and returns false if it fails to open
    * In the case of output, if the file does not exist, create the file
  * Input (<): Reads from the given file
  * Output (<): Writes to the given file
  * Output (<<): Appends to the given file
  * Never actually runs the execute() command like the other 
* Added Pipe as a Connector class
  * Makes use of pipe() in the class
  * Using fork, this takes the output of the child process and passes that as an input into the parent process.
  * This will return true if piping is successful
* Note: We were unable to implement pipe successfully. In addition, while InputRedirection works in the unit tests, it does not run properly in the shell itself.
