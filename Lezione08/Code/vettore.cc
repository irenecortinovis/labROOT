#include <iostream>
#include "vettore.h"

// ----------- CONSTRUCTORS AND DESTRUCTOR --------------

//ctor
vettore::vettore()
{
	vec = new int;
	vec[0] = 0;
	size_p = 1;
	std::cout << " vector created" << std::endl;
}

//ctor with size
vettore::vettore(const int &size)
{
	vec = new int[size];
	for(int i=0; i<size; i++)
	{
		vec[i] = 0;
	}
	size_p = size;
	std::cout << " vector with size created" << std::endl;
}

//dtor
vettore::~vettore()
{
	delete[] vec;
	std::cout << " vector deleted" << std::endl;

}


// ----------------- METHODS --------------------

int vettore::getSize(){
	return size_p;
}

//access entry
int vettore::getEntry(const int &nEntry)
{
	/*
	if(nEntry > size_p)
	{
		std::cout << "Error: number of entry exceeds vector size" << std::endl;
		return;
	}
	*/
	return vec[nEntry];
}

void vettore::print()
{
	for(int i=0; i< this->getSize(); i++)
	{
		std::cout << i << ":\t" << this->getEntry(i) << std::endl;
	}
}

//push
const vettore& vettore::push(const int& number){
	int* temp = new int[size_p+1];
	for(int i=0; i<size_p; i++)
	{
		temp[i] = vec[i];
	}
	temp[size_p] = number;

	delete[] vec;
	this->vec = temp;
	this->size_p = size_p+1;

	return *this;
}

//pop
void vettore::pop(){
	size_p = size_p-1;
	return;
}
