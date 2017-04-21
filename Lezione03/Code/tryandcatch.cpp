/*
generate random numbers following some distribution

compile with:
c++ -o tryandcatch.o ../Code/tryandcatch.cpp ../../labII.cc
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../../labII.h"




int main(){

	srand(time(NULL));

	int max_num = 10;
	double randnum;

	for (int i=0; i<max_num; i++)
	{
		randnum = rand_TryAndCatch(f_gaus, -1, 1, 0, 1);
		std::cout << randnum << std::endl;
	}

	return 0;
}