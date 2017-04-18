/*
generare N numeri casuali secondo una pdf data (Try & Catch)
scrivere i numeri estratti in un file
restituire al main il valore medio e la deviazione standard

compile with
c++ ../../labII.cc ../Code/TACanalysis.cpp -o TACanalysis.o
*/


#include <iostream>
#include <fstream>
#include <cmath>
#include "../../labII.h"


double* data_analysis(const char* path)
{
	double * values = new double[3];

	//open file
	std::ifstream infile;
	infile.open(path, std::ios::in);
	//check if it is good
	if(infile.good()==0)
	{
		std::cout << "Errore! Impossibile aprire file" << path << std::endl;
	}

	//initialise variables
	int n = 0;
	double sum = 0;
	double sum2 = 0;
	double mean;
	double variance;

	//do maths
	double a;
	while(infile >> a)
	{
		sum += a;
		sum2 += a*a;
		n++;
	}

	//fill number vector
	values[0] = n;
	//fill mean vector
	mean = sum / n;
	values[1] = mean;
	//fill error vector
	variance = sum2 / (n) - mean * mean;
	values[2] = sqrt(variance / n);

	//close file
	infile.close();
	return values;
}

int main(){

	//write TAC generated random numbers onto a file
	double randnum;
	int nRepeats = 1000;
	std::ofstream outfile ("../Data/outFile.txt", std::ios::out);
	for(int i=0; i<nRepeats; i++)
	{
		randnum = rand_TryAndCatch(f_gaus, -1, 1, 0, 1);
		outfile << randnum << std::endl;
	}
	outfile.close();

	/*
	//using data_analysis in labII.h
	//array which will contain n of measures, mean, error of mean
	double * result = new double[3];
	//perform analysis on file
	data_analysis("../Data/outFile.txt", result);
	*/

	double* result = data_analysis("../Data/outFile.txt");


	//print the result
	std::cout <<"Number of measures: " << result[0] <<
				";\t Mean: " << result[1] << ";\t Stdev: " << result[2] << std::endl;

	return 0;
}

