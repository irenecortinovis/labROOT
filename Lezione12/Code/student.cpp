/*


compile with:
c++ ../Code/student.cpp ../../labII.cc -o student.o `root-config --cflags --glibs`
*/


#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TMath.h>
#include "../../labII.h"




int main(){

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);

	//write a file with random numbers from gaussian distribution
	srand(time(NULL));
	
	int N = 50000;

	std::ofstream outfile ("../student.txt", std::ios::out);
	for(int i=0; i<N; i++)
	{
		double randnum = rand_TryAndCatch(f_gaus, -2, 2, 0, 1);
		outfile << randnum << std::endl;
	}
	outfile.close();

	//analyse data
	double* data = data_analysis("../student.txt");
	std::cout << "n: " << data[0] << "\nmean: " << data[1] << "\nstd error: " << data[2] << std::endl;

	TH1F* histo = new TH1F("z distribution", "z distribution", 500, -1000, 1000);
	double z;

	std::ifstream infile;
	infile.open("../student.txt", std::ios::in);
	double num;
	while(infile >> num)
	{
		z = (num-data[1])/data[2];
		histo->Fill(z);
	}
	infile.close();

	

	//student distribution
	//TF1* student = new TF1("student","TMath::Student(x,[0])", -1000, 1000);
	//student->SetParameter(0, data[0]); 
	int gdl = data[0];
	//student_PDF(gdl)->Draw();
 

	TCanvas* c1 = new TCanvas("z distribution");
	histo->Draw();
	//student->Draw("same");
	//student->Draw();




	Grafica->Run();


	return 0;
}