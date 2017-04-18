/*
compile with
c++ -o istogramma.o ../Code/istogramma.cc ../Code/istogramma.cpp
*/


#include "istogramma.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>



int main(){

	//creo l'istogramma
	float min = 0.;
	float max = 1.;
	std::cout << "Inserisci gli estremi dell'istogramma (min, max): ";
	std::cin >> min >> max;

	int nBin = 0;
	std::cout << "Inserisci il numero di bin dell'istogramma: ";
	std::cin >> nBin;

	//ctor
	istogramma histo(nBin, min, max);

	//riempio l'istogramma
	histo.Fill(3.14);
	histo.Fill(1.2);
	histo.Fill(2.55);
	histo.Fill(3.4);
	histo.Print();

	//default ctor
	istogramma a;
	istogramma b;
	istogramma c;

	//operator =
	//a is modified
	a = b;
	//c->b->a
	a = b = c;

	return 0;
}