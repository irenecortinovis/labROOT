/*
compile with:
c++ ../Code/raindrops.cpp ../../labII.cc -o raindrops.o `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>
#include <TH1F.h>
#include <TH2F.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include "../../labII.h"



int main(){

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);

	//open file
	std::ifstream infile;
	infile.open("../raindrops.txt", std::ios::in);
	//check if it is good
	if(infile.good()==0)
	{
		std::cout << "Errore! Impossibile aprire file " << std::endl;
	}

	//-------------- TH2F -------------

	//create TH2F
	int nbin = 10;
	TH2F* histo2D = new TH2F("Raindrops 2D", "Raindrops 2D", nbin, 0, 10, nbin, 0, 10);

	//fill TH2F
	double x, y;
	while(infile >> x >> y)
	{
		histo2D->Fill(x, y);
	}

	//close file
	infile.close();

	//draw TH2F
	TCanvas* c1 = new TCanvas("Raindrops");
	histo2D->Draw("COLZ");



	// ------------ TH1F -------------

	//create TH1F
	TH1F* histo = new TH1F("Raindrops frequency", "Raindrops ferquency", nbin, 0, 10);

	//fill TH1F and find mean
	double sum = 0;
	int counter = 0;
	for(int i=0; i<nbin; i++)
	{
		for(int j=0; j<nbin; j++)
		{
			int frequency = histo2D->GetBinContent(i,j);
			histo->Fill(frequency);
			counter++;
			sum += frequency;
		}
	}
	//mean
	double mean = sum/counter;
	std::cout << mean << std::endl;


	// --------- FIT --------------

	//TF1 gauss
	TF1* gauss = new TF1("gauss", "gaus");

	//TF1 poisson
	TF1* poisson = new TF1("poisson", "100*TMath::Poisson(x,[0])");
	poisson->SetParameter(0, mean);

	

	//draw and fit TH1F
	TCanvas* c2 = new TCanvas("Raindrops frequency");
	
	histo->Fit("gauss");
	std::cout << "Chi square gauss fit:\t" << gauss->GetChisquare() << std::endl;
	
	histo->Fit("poisson");
	std::cout << "Chi square poisson fit:\t" << poisson->GetChisquare() << std::endl;
	histo->Draw("");



	Grafica->Run();

	return 0;
}