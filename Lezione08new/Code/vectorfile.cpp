/*
Scrivere un programma che usi la classe vector del C++, richieda un
input da tastiera degli elementi del vettore e poi scriva gli elementi in un file.
N.B. cin.eof() diventa VERO quando si dà in input un ~D (CTRL D).

compile with:
c++ ../Code/vectorfile.cpp -o vectorfile.o

*/

#include <iostream>
#include <fstream>
#include <vector>

int main(){

	std::vector<int> input;
	int number;

	std::cout << "type int numbers, to stop press CTRL+D" << std::endl;


	while(!std::cin.eof())
	{
		std::cin >> number;
		input.push_back(number);
	}


	std::ofstream outfile("vectorfile.txt", std::ios::out);
	//size -1 because the last one is repeated
	for(int i=0; i<(input.size()-1); i++)
	{
		outfile << input[i] << std::endl;
	}

	outfile.close();




	return 0;
}