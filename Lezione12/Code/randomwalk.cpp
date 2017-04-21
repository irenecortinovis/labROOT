/*

compile with:
c++ ../Code/randomwalk.cpp ../../labII.cc -o randomwalk.o `root-config --cflags --glibs`
*/


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <TGraph.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TMultiGraph.h>
#include "TStyle.h"
#include "../../labII.h"



int main(){

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);

	srand(time(NULL));

	//set initial variables 
	double stepLength = 1;
	int nStep = 100;
	int nIterations = 10000;
	int nBin = 200;

	//prepare TH1Fs
	TH1F* xHisto = new TH1F("X final coordinate", "X final coordinate", nBin,
							-nStep*stepLength/4, nStep*stepLength/4);
	TH1F* yHisto = new TH1F("Y final coordinate", "Y final coordinate", nBin,
							-nStep*stepLength/4, nStep*stepLength/4);
	TH1F* distanceHisto = new TH1F("Final distance", "Final distance", nBin,
									0, nStep*stepLength/4);

	//prepare TGraphs
	int ngraphs = 2;
    TGraph *mygraf[ngraphs];
    TMultiGraph *mygrstack= new TMultiGraph();
	for (int ngr=0; ngr<ngraphs; ngr++) {
		mygraf[ngr]= new TGraph();
		mygraf[ngr]->SetPoint(0, 0, 0);
		mygraf[ngr]->SetLineColor(ngr+2);
		mygrstack->Add(mygraf[ngr]);
		}


	for(int j=0; j<nIterations; j++)
	{
		double xCoord = 0;
		double yCoord = 0;

		for(int i=0; i<nStep; i++)
		{
			/*estrarre un numero casuale tra 0 e 2 PiGreco da una
			distribuzione uniforme per determinare la direzione del passo;*/
			double theta = rand_range(0., 2*M_PI);

			/*aggiornare i valori delle coordinate (x, y) supponendo che
			il passo sia di lunghezza pari a 1;*/
			xCoord += cos(theta)*stepLength;
			yCoord += sin(theta)*stepLength;

			if(j<ngraphs)
			{
				mygraf[j]->SetPoint(i+1, xCoord, yCoord);
			}
		}

		/*calcolare la distanza R a cui il soggetto è arrivato rispetto
		al punto di partenza e le coordinate X e Y del punto di arrivo*/
		double distance = sqrt(xCoord*xCoord + yCoord*yCoord);
		
		//inserire final X, final Y e distance nei TGraph
		xHisto->Fill(xCoord);
		yHisto->Fill(yCoord);
		distanceHisto->Fill(distance);
	}

	//fit the histograms
	TF1* fitX = new TF1("fitX", "gaus", -30, 30);
	fitX->SetParameter(1, 0);
	fitX->SetParameter(2, xHisto->GetRMS());

	TF1* fitY = new TF1("fitY", "gaus", -30, 30);
	fitY->SetParameter(1, 0);
	fitY->SetParameter(2, yHisto->GetRMS());
	

	//draw the histograms
	TCanvas* c1 = new TCanvas("Random Walk X, Y, distance");
	c1->Divide(0,3);

	c1->cd(1);
	xHisto->Fit("fitX", "L");
	double chi1 = fitX->GetChisquare();
	xHisto->Draw();

	c1->cd(2);
	yHisto->Draw();
	yHisto->Fit("fitY", "L");
	double chi2 = fitY->GetChisquare();

	c1->cd(3);
	distanceHisto->Draw();


	//draw the graphs
	TCanvas* c2 = new TCanvas("c2","Random paths");
    mygrstack->Draw("APL");


	Grafica->Run();

	return 0;
}

