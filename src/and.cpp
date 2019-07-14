#include <iostream>
#include <cstdlib>
#include "../header/and.hpp"

/*Base constructor*/
And::And() : Connector() {}

/*Sets left and right children of And to those of Connector*/
And::And(Base* leftCommand, Base* rightCommand) : Connector(leftCommand, rightCommand) {}

/*If both left and right are true, then this instance of And returns true*/
/*Otherwise return false*/
bool And::execute(int in, int out) {
	return (left->execute(in, out)) &&  (right->execute(in, out));
}

