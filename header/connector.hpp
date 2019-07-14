#ifndef __CONNECTOR_HPP__
#define __CONNECTOR_HPP__

#include "base.hpp"

class Connector : public Base {
	protected:
		Base* left;
		Base* right;
	public:
		/*Connector will take in left and right arguments to decide how commands should be run*/

		/*Constructors*/
		Connector() {
			left = NULL;
			right = NULL;
		}

		Connector(Base* l, Base* r) {
			left = l;
			right = r;
		}

		virtual bool execute(int, int) { } /*execute() to be defined in connector's children*/
		virtual std::string getString() { }
};

#endif //__CONNECTOR_HPP__

