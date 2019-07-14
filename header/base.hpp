#ifndef __BASE_HPP__
#define __BASE_HPP__

#include <iostream>
#include <cstdlib>

class Base {
	public:
		//Constructor
		Base() {};
	
		/*Virtual Functions*/
		virtual bool execute(int, int) = 0; /*Execute will return a bool value*/
		virtual std::string getString() = 0;
};

#endif //__BASE_HPP__

