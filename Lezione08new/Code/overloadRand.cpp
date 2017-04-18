/*
Implementare la funzione di estrazione di un numero casuale da una
distribuzione uniforme (rand_RANGE) per int e double usando la tecnica
dell'overload. Verificare – effettuando N=10000 estrazioni – l'uniformità della
distribuzione. Per farlo riempire un vector con le frequenze dei numeri estratti.

compile with:
c++ ../../labII.cc ../Code/overloadRand.cpp -o overloadRand.o

*/




#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "../../labII.h"


int main(){

	srand(time(NULL));

	int minint = 1;
	int maxint = 20;

	//initialize vector
	std::vector<int> distribution;
	for(int i=0; i<(maxint-minint+1); i++)
	{
		distribution.push_back(0);
	}

	int N = 10000;
	int randint;

	//create random numbers and fill in distribution vector
	for (int i=0; i<N; i++)
	{
		randint = rand_range(minint, maxint);
		for(int j=minint; j<=maxint; j++)
		{
			if(randint==j)
			{
				distribution.at(j-minint)++;
			}
		}		
	}

	//print vector showing i+minint
	for(int i=0; i<distribution.size(); i++)
	{
		std::cout << i+minint << ":\t" << distribution.at(i) << std::endl;
	}

	return 0;
}