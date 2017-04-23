/*


compile with:
c++ ../Code/student.cpp ../../labII.cc -o student.o `root-config --cflags --glibs`
*/


#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "TSystem.h"
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TMath.h>
#include "../../labII.h"

/*
double MyStudent (double *x, double *par){
    		
        double enne=par[0];  //par[0] = numero gradi libertà  
        double fval = 1/sqrt(pi*par[0])*tgamma((enne+1)/2)/tgamma(enne/2);
        fval = fval*pow(1+x[0]*x[0]/enne,-1*(enne+1)/2);
        return fval;
}
*/


int main(){

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	gSystem->Load("libMathMore");	


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

	TCanvas* c1 = new TCanvas("z distribution");
	histo->Draw();

	//student distribution
	
	int ndf = data[0];

	TF1* pdfStudent = new TF1("pdfStudent", "ROOT::Math::tdistribution_pdf(x,[0])", -5,5);
   	pdfStudent->SetParameter(0,ndf);

   	TCanvas *c2 = new TCanvas("DistCanvas", "Student Distribution graphs", 10, 10, 1000, 800);
   	pdfStudent->SetTitle("Student t distribution function");
   	c2->cd();
   	pdfStudent->SetLineWidth(2);
   	pdfStudent->DrawCopy();




	Grafica->Run();


	return 0;
}