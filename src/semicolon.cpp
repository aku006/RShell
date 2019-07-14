#include <iostream>
#include "../header/connector.hpp"
#include "../header/semicolon.hpp"

Semicolon::Semicolon() : Connector() {}

Semicolon::Semicolon(Base* leftCommand, Base* rightCommand) : Connector(leftCommand, rightCommand) {}

/*If right runs successfully, then Semicolon is true*/
/*Otherwise return false*/
bool Semicolon::execute(int in, int out) {
        left->execute(in, out);
	return right->execute(in, out);
}

