/*
compile with:

c++ data.cc dataclass.cpp -o dataclass.o

*/


#include <iostream>
#include "data.h"

int main(){

	//constructor
	int day = 3;
	int month = 10;
	int year = 1996;
	data test(day, month, year);
	std::cout << "Testing default constructor: " << std::endl;
	test.stampa();

	//copy constructor
	data testCopy(test);
	std::cout << "Testing copy constructor: " << std::endl;
	testCopy.stampa();

	//operator =
	data testAssign = test;
	std::cout << "Testing = operator: " << std::endl;
	testAssign.stampa();

	//operator ==
	data testSame1(4, 10, 1996);
	data testSame2(3, 11, 1996);
	data testSame3(3, 10, 1997);
	std::cout << "Testing == constructor: " << std::endl;
	if(test == testSame1) std::cout << "error" << std::endl;
	else std::cout << "ok\t";
	if(test == testSame2) std::cout << "error" << std::endl;
	else std::cout << "ok\t";
	if(test == testSame3) std::cout << "error" << std::endl;
	else std::cout << "ok\t";
	if(test == testCopy) std::cout << "ok" << std::endl;
	else std::cout << "error" << std::endl;

	






	return 0;
}