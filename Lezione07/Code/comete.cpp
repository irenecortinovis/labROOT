/*
Dati
	/cometa1
		/coory_x1.txt
		/coory_x2.txt
		/coory_x3.txt
		/coory_x5.txt
		/coory_x7.txt
		/coory_x10.txt
	/cometa2
	/cometa3


compile with:
c++ ../../labII.cc ../Code/comete.cpp -o comete.o
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../../labII.h"


int main(){

	//vector of x positions
	std::string x[6] = {"1", "2", "3", "5", "7", "10"};
	//number of comet (input)
	int n_cometa;
	//vector of n of y measured
	double number[6];
	//vector of y positions
	double y[6];
	//vector of y error
	double erry[6];

	std::string path_begin = "../Data/cometa";

	std::cout << "type n of comet to be analysed: ";
	std::cin >> n_cometa;
	
	//cycle on folders and name of files

	for(int j=0; j<6; j++)
	{
		//create complete path of file
		std::string complete_path;
		complete_path = path_begin + char ('0' + n_cometa) + "/coory_x" + x[j] + ".txt";
		std::cout << complete_path << std::endl;

		//array which will contain n of measures, mean, error of mean
		double * values = new double[3];
		//perform analysis
		data_analysis(complete_path.c_str(), values);

		//fill number vector
		number[j] = values[0];
		//fill mean vector
		y[j] = values[1];
		//fill error vector
		erry[j] = values[2];
		std::cout <<"Number of measures: " << number[j] <<
				";\t Mean: " << y[j] << ";\t Stdev: " << erry[j] << std::endl;
	}
	
	return 0;
}