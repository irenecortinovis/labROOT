#include "istogramma.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>


//default constructor
istogramma::istogramma()
{
	nBin_p = 100;
	min_p = 0;
	max_p = 1;
	invStep_p = nBin_p/(max_p-min_p);
	binContent_p = new int[nBin_p];
	entries_p = 0;
	sum_p = 0.;
	sum2_p = 0.;
	{
		//azzero gli elementi dell'istogramma
		for (int i=0; i<nBin_p; ++i)
			binContent_p[i] = 0;
	}
	std::cout << "histogram built with default constructor!" << std::endl;
}


//constructor with initialised data
istogramma::istogramma(const int &nBin, const float &min, const float &max)
{
	nBin_p = nBin;
	min_p = min;
	max_p = max;
	invStep_p = nBin_p/(max_p-min_p);
	binContent_p = new int[nBin_p];
	entries_p = 0;
	sum_p = 0.;
	sum2_p = 0.;
	{
		//azzero gli elementi dell'istogramma
		for (int i=0; i<nBin_p; ++i)
			binContent_p[i] = 0;
	}
	std::cout << "histogram built with initialised constructor!" << std::endl;
}

//copy ctor
istogramma::istogramma(const istogramma& original)
{
	nBin_p = original.nBin_p;
	min_p = original.min_p;
	max_p = original.max_p;
	invStep_p = original.invStep_p;
	binContent_p = new int[original.nBin_p];
	entries_p = original.entries_p;
	sum_p = original.sum_p;
	sum2_p = original.sum2_p;
	{
		//azzero gli elementi dell'istogramma
		for (int i=0; i<nBin_p; ++i)
			binContent_p[i] = original.binContent_p[i];
	}
	std::cout << "histogram built with copy constructor!" << std::endl;
}
	

istogramma::~istogramma()
{
	delete[] binContent_p;
	std::cout << "histogram deleted!" << std::endl;
}



//operator =()

/*
A copy constructor is used to initialize
a previously uninitialized object from some other object's data.

An assignment operator is used to replace the data
of a previously initialized object with some other object's data.
*/

istogramma& istogramma::operator=(const istogramma& original)
{
	if(binContent_p) delete[] binContent_p;
	nBin_p = original.nBin_p;
	min_p = original.min_p;
	max_p = original.max_p;
	invStep_p = original.invStep_p;
	binContent_p = new int[original.nBin_p];
	entries_p = original.entries_p;
	sum_p = original.sum_p;
	sum2_p = original.sum2_p;
	{
		//azzero gli elementi dell'istogramma
		for (int i=0; i<nBin_p; ++i)
			binContent_p[i] = original.binContent_p[i];
	}

	return *this;
}


int istogramma::Fill(const float& value)
{
	if (value < min_p)
	{
		std::cout << "ERROR: underflow";
		return -1;
	}
	if (value >= max_p)
	{
		std::cout << "ERROR: overrflow";
		return -1;
	}
	else
	{
		++entries_p;

		int bin = int((value-min_p)*invStep_p);
		++binContent_p[bin];
		sum_p += value;
		sum2_p += value*value;
		return bin;
	}
}


void istogramma::Print() const
{
	//normalizza l'istogramma al valore maggiore
	int max = 0;
	for (int i=0; i<nBin_p; ++i)
	{
		if(binContent_p[i]>max)
			max = binContent_p[i];
	}

	//fattore di dilatazione per rappresentazione istogramma
	int scale = 50;

	//disegna asse y
	std::cout << "        +---------------------------------------------------->"
	<< std::endl;

	//disegna il contenuto dei bin
	for (int i=0; i<nBin_p; i++)
	{
		std::cout << std::fixed << std::setw(8) << std::setprecision(2)
		<< min_p + i / invStep_p << "|";
		int freq = int(scale * binContent_p[i] / max);
		for (int j=0; j<freq; ++j)
			std::cout << "#";
		std::cout << std::endl;
	}

	std::cout << "        |\n" << std::endl;
}
