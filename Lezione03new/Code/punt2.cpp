/* Dichiarate un puntatore e poi cercate di assegnargli
direttamente un valore numerico. Cosa succede? Perchè? */

//c++ ../Code/punt2.cpp -o punt2

#include <iostream>

int main(){

	int * pointer;
	*pointer = 100;
	//std::cout << "address: " << pointer << "\tvalue: " << &pointer << std::endl;

	return 0;
}