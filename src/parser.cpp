#include <iostream>
#include <stdlib.h>
#include "../header/parser.hpp"
/*#include "../header/base.hpp"
#include "../header/and.hpp"
#include "../header/or.hpp"
#include "../header/semicolon.hpp"*/
//#include "../unit_tests/mockCommand.hpp"

Parser::Parser() {}

Parser::Parser(std::string input) {
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(" ");
	
	//std::vector<Base*> exec;
	std::vector<std::string> conn;
	std::vector<std::string> conn2; //creates a vector for connectors inside a parenthesis
	std::vector<std::string> cmd;
	std::vector<std::string> conv; //transfer contents from token to vector
	std::vector<Base*> exec;
	
	std::string temp; //store consecutive tokens that can be used to make cmds
	Base* str1;
	Base* str2;
	std::string conTemp;
	std::string conTemp2;

	int quoteFlag = 0;
	bool oneWord = false;
	bool firstParFlag = false; //flag for first parenthesis

	/* if(input.find("\"") {
		quoteFlag = 1; //if quotes are present, raise the flag
	} */

	//int hash = input.find_first_of("#"); //find first instance of '#'
	//hash addressed somewhere

	//std::string hashUpdate = input.substr(0, hash); //make new string to tokenize based on where first "#"
	//if user simply enters, addresses empty input as well
	if(input == "") {
		//std::cout << "empty???" << std::endl;
		return;
	}
	
	//tokenizes input into words
	tokenizer tok(input, sep);

	for(boost::tokenizer<boost::char_separator<char> >::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
		conv.push_back(*beg);
	}
	
	for(unsigned i = 0; i < conv.size(); ++i) {
		//std::cout << conv.at(i) << std::endl;
	 	if (conv.at(i).find("(") != std::string::npos) {
			firstParFlag = true;
			if (conv.at(i).size() == 1) {
				//std::cout << "yeet 1" << std::endl;
				temp = temp + conv.at(++i) + " ";
				++i;
			}
			else {
				//std::cout << "yeet 2" << std::endl;
				std::string cut = conv.at(i).substr(conv.at(i).find("(")+1);
				temp += cut + " ";
			}
		}

		else if (conv.at(i).find(")") != std::string::npos) {
			firstParFlag = false;
			//std::cout << "yeet 3" << std::endl;
			//There should be data left in temp and conn2, so force those into objects
			if (conv.at(i).size() == 1) {
				//do nothing, desired code is already in temp
			} else {
				std::string cut = conv.at(i).substr(0, conv.at(i).find(")"));
				temp += cut + " ";
			}
			//std::cout << "yeet3 temp print "<<temp << std::endl;
			Command* nein2 = new Command(temp);
			//std::cout << "yeet 3-1" << std::endl;
			if(exec.size() != 0 ) {
				str2 = exec.back(); exec.pop_back();
				conTemp2 = conn2.back();
				if (conTemp2 == "&&") {
					And* non = new And(str2, nein2);
					exec.push_back(non);
				}
				else if (conTemp2 == "||") {
					Or* non = new Or(str2, nein2);
					exec.push_back(non);
				}	
				else if (conTemp2 == ";") {
					Semicolon* non = new Semicolon(str2, nein2);
					exec.push_back(non);
				}
				conn2.pop_back();//caused seg fault
				temp = "";
			} else {
				//std::cout << "yeet 3-2" << std::endl;
				exec.push_back(nein2);
				temp = "";
			}
		}

		else if (conv.at(i).find("\"") != std::string::npos ) {
			oneWord = true;
			//std::cout << conv.at(i) << std::endl;
			//both quotes around ONE WORD???
			//std::cout << "quoteFlagged" << std::endl;
			
			if (oneWord && conv.at(i).rfind("\"") != conv.at(i).find("\"")) {
				temp = temp + conv.at(i) + " ";
				oneWord = false;
			}

			else if (quoteFlag < 1) {//make it two and the second work with quotes wont be inc'd correctly
				++quoteFlag;
				temp = temp + conv.at(i) + " ";
			} else {
				quoteFlag = 0;
				temp = temp + conv.at(i) + " ";
			} 

		} else if (conv.at(i).find("#")!= std::string::npos)  {
			if (!quoteFlag) {
				//std::cout << "hash break" << std::endl;
				break;
			}
			//break;//if token contains # and it isn't within quotations, break
		} else if ( (conv.at(i).find(";") != std::string::npos) && conv.at(i).size() > 1) {
			//if (conn.size() == 0) {
			//std::cout << "semicolon" << std::endl;
			std::string cut = conv.at(i).substr(0, conv.at(i).find(";"));
			temp = temp + cut + " ";
			Command *nein = new Command(temp);
			exec.push_back(nein);
			temp = "";
			conn.push_back(";");

		} else if ( (conv.at(i) == ">") || (conv.at(i) == "<") || (conv.at(i) == ">>") || (conv.at(i) == "|") && !quoteFlag){
			//exec.back()->get_string()???
			std::cout << temp << std::endl;
			if(conn.size() == 0) {
				if(temp == "") {
					conn.push_back(conv.at(i));
				} else {
					Command *nein = new Command(temp);
					exec.push_back(nein);
					temp = "";
					conn.push_back(conv.at(i));
				}
			} else if (conn.size() == 1) {
				//std::cout << temp << std::endl;
				Command *nein2 = new Command(temp); //right cmd is stored in temp
				str2 = exec.back(); exec.pop_back();
				conTemp = conn.back();
				if (conTemp == "&&") {
					And *non = new And(str2, nein2);
					exec.push_back(non);
				} else if (conTemp == "||") {
					Or *non = new Or(str2, nein2);
					exec.push_back(non);
				}  else if (conTemp == ";") {
					Semicolon *non = new Semicolon(str2, nein2);
					exec.push_back(non);
				}  /* else if (conTemp == "|") {
					Pipe *non = new Pipe(str2, nein2);
					exec.push_back(non);
				}  */else if (conTemp == "<") {
					SingleOutRedirection *non = new SingleOutRedirection(str2, nein2);
					exec.push_back(non);
				}  else if (conTemp == ">") {
					InputRedirection *non = new InputRedirection(str2, nein2);
					exec.push_back(non);
				}  else if (conTemp == ">>") {
					DoubleOutRedirection *non = new DoubleOutRedirection(str2, nein2);
					exec.push_back(non);
				} 
				
				conn.pop_back();
				temp = "";
				conn.push_back(conv.at(i));			
			}
			
		} else if ( ((conv.at(i) == "&&") || (conv.at(i) == "||") || (conv.at(i).find(";") != std::string::npos) ) && !quoteFlag) {

			if (!firstParFlag) {
				if(conn.size() == 0) {
					//std::cout << "connectors1 " << exec.size() << " " << std::endl;
					if (temp == "") { //sometimes, after parsing a parentheses, there maybe nothing in temp to work with
						conn.push_back(conv.at(i));
					} else {
						Command *nein = new Command(temp);
						exec.push_back(nein);
						temp = "";
						conn.push_back(conv.at(i));
					}
				}

				else if (conn.size() == 1) {
					//std::cout << "connectors2" << std::endl;
					Command *nein2 = new Command(temp); //right cmd is stored in temp
					str2 = exec.back(); exec.pop_back();
					conTemp = conn.back();
					if (conTemp == "&&") {
						And *non = new And(str2, nein2);
						exec.push_back(non);
					} else if (conTemp == "||") {
						Or *non = new Or(str2, nein2);
						exec.push_back(non);
					}  else if (conTemp == ";") {
						Semicolon *non = new Semicolon(str2, nein2);
						exec.push_back(non);
					} 
					
					conn.pop_back();
					temp = "";
					conn.push_back(conv.at(i));
				}
			}

			else {
				if(conn2.size() == 0) {
					//std::cout << "yeet 4" << std::endl;
					Command *nein = new Command(temp);
					exec.push_back(nein);
					temp = "";
					conn2.push_back(conv.at(i));
				}
				else if (conn2.size() == 1) {
					//std::cout << "yeet 5" << std::endl;
					Command* nein2 = new Command(temp);
					str2 = exec.back(); exec.pop_back();
					conTemp2 = conn2.back();
					if (conTemp2 == "&&") {
						//std::cout << "yeet 6" << std::endl;
						And* non = new And(str2, nein2);
						exec.push_back(non);
					}
					else if (conTemp2 == "||")  {
						//std::cout << "yeet 7" << std::endl;
						And* non = new And(str2, nein2);
						exec.push_back(non);
					}
					else if (conTemp2 == ";") {
						//std::cout << "yeet 8" << std::endl;
						Semicolon* non = new Semicolon(str2, nein2);
						exec.push_back(non);
					}

					conn2.pop_back();
					temp = "";
					conn2.push_back(conv.at(i));
				}
			}
		}		

		else {
			temp = temp + conv.at(i) + " ";
			//std::cout << i << " yeet 9 " << temp << std::endl;
		} 
	}

	//addresses that one last command that wasn't read in the for loop
	//and/or if there's only one command
	//std::cout << "temp out of loop: " << temp << std::endl;
	if(temp != "") {
		//std::cout << "out of loop " << temp << std::endl;
		Command *nyet = new Command(temp);
		if (conn.size() == 1) {
			//std::cout << conn.back() << std::endl;
			std::cout << temp << std::endl;
			str2 = exec.back(); exec.pop_back();
			std::cout << "str2 " << str2->getString() << std::endl;
			conTemp = conn.back();
			//std::cout << "out of 2" << std::endl;
			if (conTemp == "&&") {
				And *non = new And(str2, nyet);
				exec.push_back(non);
			} else if (conTemp == "||") {
				Or *non = new Or(str2, nyet);
				exec.push_back(non);
			} else if (conTemp == ";") {
				Semicolon *non = new Semicolon(str2, nyet);
				exec.push_back(non);
			} else if (conTemp == ">") {
				std::cout << "yeet > " << std::endl;
				SingleOutRedirection *non = new SingleOutRedirection(str2, nyet);
				exec.push_back(non);
			}  else if (conTemp == "<") {
				InputRedirection *non = new InputRedirection(str2, nyet);
				exec.push_back(non);
			}  else if (conTemp == ">>") {
				DoubleOutRedirection *non = new DoubleOutRedirection(str2, nyet);
				exec.push_back(non);
			}
			conn.pop_back();
			temp = "";	
		} else {
			exec.push_back(nyet);
		}	
	}
	
		if (conn.size() != 0 ) {
			//std::cout << "yeet 10" <<std::endl;
			//std::cout << exec.size() << std::endl;
			std::vector<Base *> execCpy = exec;
			//(conn2 should be empty by this point)
			while(execCpy.size() > 0) {
				Base *right = execCpy.back(); execCpy.pop_back();
				Base *left = execCpy.back(); execCpy.pop_back();
				exec.pop_back(); exec.pop_back();
				conTemp2 = conn.back();
				if (conTemp2 == "&&") {
					And* non = new And(left, right);
					exec.push_back(non);
				}
				else if (conTemp2 == "||") {
					Or* non = new Or(left, right);
					exec.push_back(non);
				}	
					else if (conTemp2 == ";") {
					Semicolon* non = new Semicolon(left, right);
					exec.push_back(non);
				}
			}
			temp = "";
			//std::cout << "did this shit finish" << std::endl;
		}
	
	//std::cout <<"parser exec size" << exec.size() << std::endl;
	//exec.at(0)->execute();
	//exec.at(1)->execute();	
	this->obj = exec;
}

void Parser::execute(int in, int out) {
	if (this->obj.size() == 0) {
		return;
	}
	//std::cout << "parser execute" << std::endl;
	this->obj.at(0)->execute(in, out);
	//altho execute() of obj classes are of bool type, its ok if they're not returned to any variable
	return;
}
