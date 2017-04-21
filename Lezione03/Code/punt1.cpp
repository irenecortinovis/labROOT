/* Scrivete un programma che assegni il valore di una
variabile ad un'altra utilizzando un puntatore. Fatevi inoltre
stampare a terminale i valori e gli indirizzi di ogni variabile prima e
dopo l'assegnazione. */

//c++ ../Code/punt1.cpp -o punt1

#include <iostream>

void assign(int &var1, int &var2){
	int* tempPointer;
	tempPointer = &var1;
	var2 = *tempPointer;
	return;
}

int main(){
	
	int num1 = 10;
	int num2;
	std::cout << "num2 before: " << num2 << std::endl;
	assign(num1, num2);
	std::cout << "num2 after: " << num2 << std::endl;

	return 0;
}