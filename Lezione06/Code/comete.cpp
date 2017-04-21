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
c++ -o comete.o ../Code/comete.cpp
*/


#include <iostream>
#include <fstream>
#include <string>

int main(){

	//define all variables needed
	int n = 0;
	double sum = 0;
	double sum2 = 0;
	double mean = 0;
	double stdev = 0;
	int n_cometa[3] = {1, 2, 3};
	std::string x[6] = {"1", "2", "3", "5", "7", "10"};
	std::string path = "../Data/cometa";
	std::ifstream infile;
	
	//cycle on folders and name of files
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<6; j++)
		{
			//open file
			std::string complete_path;
			complete_path = path + char ('0' + n_cometa[i]) + "/coory_x" + x[j] + ".txt";
			std::cout << complete_path << std::endl;
			infile.open(complete_path.c_str(), std::ios::in);

			//check if it is good
			if(infile.good()==0)
			{
				std::cout << "Errore! Impossibile aprire file" << complete_path << std::endl;
				return 1;
			}

			//do maths
			double a;
			while(infile >> a)
			{
				sum += a;
				sum2 += a*a;
				n++;
			}
			mean = sum / n;
			stdev = sum2 / (n) - mean * mean;
			std::cout << "Mean: " << mean << ";\t Stdev: " << stdev << std::endl;

			//close file
			infile.close();
		}
	}

	return 0;
}