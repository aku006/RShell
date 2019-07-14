#include <iostream>
#include <cstdlib>
#include "../header/or.hpp"

/*Base constructor*/
Or::Or() : Connector() {}

/*Sets left and right children of Or to those of Connector*/
Or::Or(Base* leftCommand, Base* rightCommand) : Connector(leftCommand, rightCommand) {}

/*If either one of these returns true, then the whole Or is true*/
bool Or::execute(int in, int out) {
	return (left->execute(in, out)) || (right->execute(in, out));
}

