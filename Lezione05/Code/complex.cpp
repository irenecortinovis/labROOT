#include "complex.h"
#include <iostream>
#include <cmath>


/*
compile with:
c++ -o complex.o ../Code/complex.cc ../Code/complex.cpp
*/


int main(){

	//test default constructor
	complex a;
	a.Print();

	//test constructor re and im
	complex b(20, 0.3);
	b.Print();

	//test constructor rho and theta
	complex test(1.41, 0.79, "--flag");
	test.Print();

	//test methods
	complex c(1,1);
	c.Print();
	std::cout << c.Re() << "\t" << c.Im() << "\t"
			<< c.Mod() << "\t" << c.Theta()*180/M_PI << "°\t" << std::endl;

	//test operator =
	complex d;
	d = c;
	d.Print();

	//test operator +
	complex e;
	e = (b+d);
	e.Print();



	return 0;
}