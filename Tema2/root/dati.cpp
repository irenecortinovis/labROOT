/*
compile with:
c++ dati.cpp -o dati.o `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <TH1F.h>
#include <TH2F.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <TGraph.h>

//function for probability of particle not passing through x U.A. thickness
double f_probability(double x, double f_E){
	return exp(-x*f_E);
}

//returns a random number from uniform distribution between min and max
double rand_range(double min, double max){
	return min + (max - min) * rand() / (RAND_MAX);
}

//pdf function
double f_pdf(double x){
	return (2./25. * (-x+5.));
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


int main(){

	srand(time(NULL));

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);

	//TGraphErrors from file
	TGraphErrors* graph = new TGraphErrors("dati_f.txt");
	graph->SetTitle("Energy");

	//fit
	TF1* funz1 = new TF1("funz1", "[0]*exp(-[1]*x)");
	TF1* funz2 = new TF1("funz2", "[0]/x + [1]");

	graph->Fit("funz1");
	double chi2_1 = funz1->GetChisquare();
	std::cout << "chi quadro ridotto funz 1: " << chi2_1/8 << std::endl;

	graph->Fit("funz2");
	double chi2_2 = funz2->GetChisquare();
	std::cout << "chi quadro ridotto funz 2: " << chi2_2/8 << std::endl;

	//prepare canvas
	TCanvas* c1 = new TCanvas("Energy");
	//draw (fit funz2)
	graph->Draw();


	//save parameters in array
	double par[2] = {funz2->GetParameter(0), funz2->GetParameter(1)};


	//----------- TH1F ----------

	//create TH1F
	int nbin = 100;
	double xmin = 0;
	double xmax = 5;
	double thickness = 5; //U.A.

	int N = 1000;

	//histogram for the PDF function of the energy of the particles
	TH1F* histo = new TH1F("PDF Energy", "PDF Energy", nbin, xmin, xmax);
	
	//histogram for the particles not absorbed
	TH1F* passHisto = new TH1F("Particles going through x U.A. thickness", 
								"Particles going through x U.A. thickness",
								nbin, xmin, xmax);


	//fill it with random numbers distributed like PDF
	for(int i=0; i<N; i++)
	{
		//energy of the particle
		double randenergy = rand_TryAndCatch(f_pdf, xmin, xmax, f_pdf(xmax), f_pdf(xmin));
		//fill histogram
		histo->Fill(randenergy);

		//probability particle NOT being absorbed in (i.e. go through) x U.A. thickness
		double probability = f_probability(thickness, funz2->Eval(randenergy));
		//random energy from uniform distribution(0, 1)
		double randnum = rand_range(0, 1);
		//if probability of going through > randnum: particle goes through so fill histogram
		if(probability>randnum)
		{
			passHisto->Fill(randenergy);
		}
	}

	TCanvas* c2 = new TCanvas("Energy");
	c2->cd();
	//draw pdf histogram
	histo->SetFillColor(5);
	histo->Draw();

	//draw pass through histogram
	passHisto->SetFillColor(6);
	passHisto->Draw("same");


	Grafica->Run();

	return 0;
}