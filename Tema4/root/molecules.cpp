/*
compile with:
c++ molecules.cpp -o molecules.o `root-config --glibs --cflags`

*/

#include <iostream>
#include <fstream>	
#include <cmath>
#include <TH1F.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TF1.h>
#include <TMath.h>

//distance between hole and opposite wall
const double dist_d = 5; //m
//gravitational acceleration
const double acc_g = 9.81; //ms-2
//k
const double k = acc_g*pow(dist_d,2)*0.5;

double MyGauss (double *x, double *par)
{
        //par[0] = coefficient because not normalized 
  		//par[1] = sigma => fhwm = par[2]*2.35
		//mean set to 0
        if(x[0] >= 0)
        	return par[0]*exp(-0.5*x[0]*x[0]/(par[1]*par[1]));
	    else return 0;
}

double fity (double *x, double *par)
{
	//par[0] = A;
	//par[1] = sigma
	return par[0]*exp(-0.5*k/(par[1]*par[1]*x[0]))*sqrt(k)*pow(x[0],(-1.5))*0.5;
}



int main(){

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);

	//histogram for initial horizontal velocity of molecules through hole
	TH1F* histovx = new TH1F("v_0x", "v_0x", 100, -40, 40);

	//histogram for point of impact (y) on the opposite wall
	TH1F* histoy = new TH1F("y", "y", 1000, 0, 40);


	//open file
	std::ifstream infile("dati.txt", std::ios::in);
	if(!infile.good())
	{
		std::cout << "impossibile aprire il file" << std::endl;
		return 1;
	}

	//point of impact
	double y;

	double entry;
	while (infile >> entry)
	{
		//fill histovx with the v0x
		histovx->Fill(entry);
		//calculate point of impact
		y = acc_g*pow(dist_d,2) / (2*pow(entry,2));
		//fill histoy with y
		histoy->Fill(y);
	}

	//close file
	infile.close();

	//fit
	//histovx
	TF1* pdfGauss = new TF1("MyGauss", MyGauss, 0, 40, 2);  
   	pdfGauss->SetParameter(0,10000); //
   	pdfGauss->SetParameter(1,10); //sigma della gaussiana

   	//histoy
   	TF1* pdfY = new TF1("fity", fity, 0, 40, 2);  
   	pdfY->SetParameter(0,1000); //A
   	pdfY->SetParameter(1,7); //sigma 

	//draw histograms and fits
	gStyle->SetOptFit(1111);

	TCanvas* c1 = new TCanvas("Initial velocity v_0x of molecules through hole");
	histovx->Draw();
   	histovx->Fit("MyGauss");

	TCanvas* c2 = new TCanvas("Point of impact on opposite wall");
	c2->cd();
	c2->SetLogx(1);
	histoy->Draw();
	histoy->Fit("fity");

	//run TApplication
	Grafica->Run();

}