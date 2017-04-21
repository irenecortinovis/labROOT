/*
find solutions of given function by using bisection method

compile with:
c++ -o bisection.o ../Code/bisection.cpp ../../labII.cc
*/

#include "../../labII.h"
#include <iostream>
#include <cstdlib>
#include <cmath>


double f_bisection(double x){
	return exp(-1 * x) - 0.5;
}


int main(){

	double precision = 0.0005;
	double xMin = 0;
	double xMax = 1;

	double solution;
	solution = bisectionRecursive(f_bisection, xMin, xMax, precision);
	std::cout << solution << std::endl;

	return 0;
}