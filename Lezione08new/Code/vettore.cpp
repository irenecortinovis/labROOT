/*
Implementare una classe vettore a dimensione variabile (come quello
che si crea con new) che si distrugge da solo alla fine dell’esecuzione che possa
contenere int, float, double ...

compile with:

c++ ../Code/vettore.cc ../Code/vettore.cpp -o vettore.o

*/


#include <iostream>
#include "vettore.h"

int main(){

	//default constructor
	vettore test;
	std::cout << "Testing default constructor: " << std::endl;
	test.print();

	//constructor w/ size
	vettore testsize(5);
	std::cout << "Testing constructor w/ size: " << std::endl;
	testsize.print();

	//test push
	testsize.push(30);
	std::cout << "Testing push function: " << std::endl;
	testsize.print();

	//test pop
	testsize.pop();
	std::cout << "Testing pop function" << std::endl;
	testsize.print();


	return 0;
}