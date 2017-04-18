#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "TStyle.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TF1.h"
#include "TF1.h"
#include <TH2F.h>
#include "TMultiGraph.h"
#include "TApplication.h"
using namespace std;


// c++ randomwalks.cpp -o rndwk  `root-config --cflags --glibs`

//funzione che prepara distribuzione uniforme
//per determinare la direzione del passo
float rand_range (float min, float max) {
	return min + (rand() * (max - min) / (float(RAND_MAX)));
}


int main(int argc, char** argv ) {



	TApplication myApp("App", &argc, argv);
	const int nWalkers = 100000;
	const int nStep = 50;

	srand(time(NULL));
	gStyle->SetOptFit(1111);

	float walkers[nWalkers][2];   // cos e sin della posizione raggiunta
	for (int i = 0; i < nWalkers; ++i) {
		walkers[i][0] = walkers[i][1] = 0;
	}

	int numg=10;
    TGraph *mygraf[numg];
    TMultiGraph *mygrstack= new TMultiGraph();
	for (int j = 0; j < numg; ++j) {
		mygraf[j]= new TGraph();
		mygraf[j]->SetPoint(0, 0, 0);
		mygraf[j]->SetLineColor(j);
		mygrstack->Add(mygraf[j]);
		}


	for (int i = 0; i < nStep; ++i) {
		for (int j = 0; j < nWalkers; ++j) {
			float direction = rand_range(0., 2.*M_PI);
			walkers[j][0] += cos(direction);
			walkers[j][1] += sin(direction);
			if (j<numg) {
				mygraf[j]->SetPoint(i+1, walkers[j][0], walkers[j][1]);
				}
		}
	}


	TH1F *histo = new TH1F("walks", "Random walks", 80, -30., 30.);
    TH1F *histox = new TH1F("walksx", "Random walks", 80, -30., 30.);
    TH1F *histoy = new TH1F("walksy", "Random walks", 80, -30., 30.);
    TH2F *pdf= new TH2F("pdf","istogramma",80,-30,30,80,-30,30);
	histo->SetLineColor(1);
    histox->SetLineColor(4);
    histoy->SetLineColor(5);

	for (int i = 0; i < nWalkers; ++i) {
		float distance = pow(walkers[i][0], 2)  + pow(walkers[i][1], 2);
		distance = sqrt(distance);
		histox->Fill(walkers[i][0]);
		histoy->Fill(walkers[i][1]);
		//~ histo->Fill(distance);
		histo->Fill(walkers[i][0]+walkers[i][1]);
		pdf->Fill(walkers[i][0],walkers[i][1]);
		//~ cout << "The walker num. " << i << " walked to a distance of: " << distance << endl;
	}

	//TF1 *funz1 = new TF1("funz1", "x*[0]*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))", 0., 30.);
	TF1 *funz1 = new TF1("funz1", "gaus", 0., 30.);
	funz1->SetParameter(0, 100.);
	funz1->SetParameter(1, 0.);
	funz1->SetParameter(2, 2.);
	histo->Fit("funz1", "L");
	double chi1 = funz1->GetChisquare();


	//~ TF1 *funz2 = new TF1("funz2", "gaus", 0., 30.);
	//~ funz2->SetLineColor(3);
	//~ funz2->SetParameter(0, 100.);
	//~ funz2->SetParameter(1, 0.);
	//~ funz2->SetParameter(2, 2.);
	//~ histo->Fit("funz2", "L+");
	//~ double chi2 = funz2->GetChisquare();


	TCanvas *c1 = new TCanvas("c1","cammino");
    mygrstack->Draw("APL");

	TCanvas *c3 = new TCanvas("c3","pdf(x,y)");
    pdf->Draw("COLZ");


    cout<<"Covarianza "<<pdf->GetCovariance()<<endl;
	cout<<"Correlation Factor "<<pdf->GetCorrelationFactor()<<endl;



	TCanvas *c2 = new TCanvas("c2");
	c2->Divide(3,1);
	c2->cd(1);
	histo->Draw();
	c2->cd(2);
	histox->Draw("same");
	c2->cd(3);
	histoy->Draw("same");

	//~ cout << "The chi square of the Gaussian fit is equal to: " << chi2 << endl;
	cout << "The chi square of the fit with the point spread function is equal to: " << chi1 << endl;

	myApp.Run();

	return 0;
}
