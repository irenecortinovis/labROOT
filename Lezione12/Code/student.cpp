/*
compile with:
c++ ../Code/student.cpp -o student.o `root-config --cflags --glibs`
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


double const pi=3.1415926535897;

//returns a random number from uniform distribution between min and max
double rand_range(double min, double max){
	return min + (max - min) * rand() / (RAND_MAX);
}


//gauss function
double f_gaus(double x){
	double mean = 0;
	double stdev = 0.5;
	return 1/sqrt(2*M_PI*stdev*stdev) * exp(-1*(x-mean)*(x-mean)/(2*stdev*stdev));
}

//generate random numbers with try and catch method
double rand_TryAndCatch(double f(double), double xMin, double xMax,
				double yMin, double yMax){
	double x = 0.;
	double y = 0.;

	do
	{
		x = rand_range(xMin, xMax);
		y = rand_range(yMin, yMax);
	} while (y > f(x));

	return x;
}


/*
opens file (checking)
calculates n of entries, mean, error of mean
saves them in array 
closes file and returns array
*/
double* data_analysis(const char* path)
{
	double * values = new double[3];

	//open file
	std::ifstream infile;
	infile.open(path, std::ios::in);
	//check if it is good
	if(infile.good()==0)
	{
		std::cout << "Errore! Impossibile aprire file " << path << std::endl;
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

	//number of entries
	values[0] = n;
	//mean
	mean = sum / n;
	values[1] = mean;
	//std error of mean
	variance = sum2 / n - mean * mean;
	values[2] = sqrt(variance / n);

	//close file
	infile.close();
	return values;
}

double MyStudent (double *x, double *par){
    		
        double enne = par[0];  //par[0] = numero gradi libertà
        double A = par[1]; //coefficient because not normalised
        long long gamma1 = tgamma((enne+1)/2);
        long long gamma2 = tgamma(enne/2);
        long double gammaquotient = (double) gamma1/(double)gamma2;
        double fval = 1/sqrt(pi*par[0])*gammaquotient;
        fval = A*fval*pow(1+x[0]*x[0]/enne,-1*(enne+1)/2);
        return fval;
}



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

	

	//student distribution
	//n degrees of freedom
	int ndf = data[0];

	//provo con quella di root
	TF1* pdfStudent = new TF1("pdfStudent", "ROOT::Math::tdistribution_pdf(x,[0])", -5,5);
   	pdfStudent->SetParameter(0,ndf);

   	TCanvas *c2 = new TCanvas("DistCanvas", "Student Distribution graphs", 10, 10, 1000, 800);
   	pdfStudent->SetTitle("Student t distribution function");
   	c2->cd();
   	pdfStudent->SetLineWidth(2);
   	pdfStudent->DrawCopy();

   	//provo con la mia (con anche un fattore perchè non è normalizzata)
	TF1* MypdfStudent = new TF1("MypdfStudent", MyStudent, -5,5,2);
   	MypdfStudent->SetParameter(0,ndf);
   	MypdfStudent->SetParameter(1,100000);

    TCanvas *Canvas = new TCanvas("Ciao", "Ciao", 10, 10, 1000, 400);
   	MypdfStudent->SetTitle("ciao");
   	Canvas->cd();
   	MypdfStudent->SetLineWidth(2);
   	MypdfStudent->DrawCopy();

   	//istogramma con la variabile t e fittato con la mia aaaa non funzionaaa
   	TCanvas* c1 = new TCanvas("z distribution");
	histo->Draw();
	histo->Fit("MypdfStudent");
   	




	Grafica->Run();


	return 0;
}