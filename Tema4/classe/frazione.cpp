/*
compile with:
c++ -o frazione.o frazione.cpp frazione.cc frazione.h
*/

#include "frazione.h"
#include <iostream>
#include <math.h>


int main()
{
	//testing constructor and destructor
	std::cout << "Testing constructor and destructor" << std::endl;
	frazione a1(1,2);
	frazione e1(-1,2);
	frazione e2(1,-2);
	frazione e3(0,1);
	frazione e4(1,0);
	frazione e5(0,0);

	a1.stampa();
	e1.stampa();
	e2.stampa();
	e3.stampa();
	e4.stampa();
	e5.stampa();

	//testing copy constructor
	std::cout << "\nTesting copy constructor" << std::endl;

	frazione a2(a1);
	a2.stampa();

	//testing operator =
	std::cout << "\nTesting operator =" << std::endl;
	frazione a3(2,3);
	a3.stampa();
	a3 = a2;
	a3.stampa();

	//testing compare
	std::cout << "\nTesting compare" << std::endl;
	frazione a4(5,6), a5(6,7), a6(-1,2);
	std::cout << a4.compara(a5) << "\t" << a5.compara(a4) << "\t" 
			  	<< a5.compara(a6) << "\t" << a6.compara(a6) << std::endl;
	 //should be -1, 1, 1, 0
	

	//testing 4 operation
	std::cout << "\nTesting + - * / operations" << std::endl;
	frazione o1(1,2), o2(2,3), o3(4,5), o4(5,7), o5(3,8);
	o1.somma(o2);
	o1.stampa(); //should be 7/6
	o2.sottrai(o3);
	o2.stampa(); //should be -2/15
	o3.moltiplica(o4);
	o3.stampa(); //should be 4/7
	o4.dividi(o5);
	o4.stampa(); //should be 40/21



	return 0;
}