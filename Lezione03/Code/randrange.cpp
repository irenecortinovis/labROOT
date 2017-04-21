/*
generating random numbers between min and max

compile with:
c++ -o randrange.o ../Code/randrange.cpp
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

int main(){

	srand(time(NULL));
	int count = 1000;

	double min = -1;
	double max = +1;

	double randnum;
	double sum = 0;
	double sumSq = 0;

	for (int i=0; i<count; i++)
	{
		randnum = min + (max - min) * rand() / (1. * RAND_MAX);
		//std::cout << randnum << std::endl;
		sum += randnum;
		sumSq += randnum * randnum;
	}

	double mean = sum / count;
	double variance = sumSq / count - mean * mean;

	std::cout << "mean: " << mean << std::endl;
	std::cout << "variance: " << variance << std::endl;

	return 0;
}