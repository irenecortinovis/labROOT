/*
find integral of function using Monte Carlo method

compile with:
c++ -o integrals.o ../Code/integrals.cpp ../../labII.cc
*/

#include "../../labII.h"
#include <iostream>
#include <cstdlib>
#include <cmath>


double function(double x){
	return exp(x);
}

int main(){


	srand(time(NULL));

	//to be changed
	double xmin = 0;
	double xmax = 1;
	double ymin = 0;
	double ymax = function(xmax)+0.1;

	std::cout << "riemann: " << integral_riemann(function, xmin, xmax, 100000) << std::endl;
	std::cout << "montecarlo: " << integral_montecarlo(function, xmin, xmax, ymin, ymax, 100000) << std::endl;

	return 0;
}