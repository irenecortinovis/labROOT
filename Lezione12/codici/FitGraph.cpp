#include <iostream>
#include <fstream>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>
//c++  FitGraph.cpp  `root-config --cflags --glibs` -o FitGraph


using namespace std;


int main(int argv, char ** argc) {

	TApplication* Grafica= new TApplication("", NULL, NULL);


	gStyle->SetOptFit(1111);
	TCanvas* c1=new TCanvas("c1","il mio canvas");
	//c1->Divide(1,2);

	TF1 *FitFunz = new TF1 ("f1","[0]*(1-exp(-x/[1]))");
	FitFunz->SetParameters(8,0.004);


	//c1->cd(2);
	TGraphErrors *gr2= new TGraphErrors("dati_TGraphErrors.txt");
	gr2->SetMarkerSize(2);
	gr2->SetMarkerStyle(20);


	int n=gr2->GetN();
	double *ex, *ey;
	ex=gr2->GetEX();
	ey=gr2->GetEY();

	for (int i=0;i<n;i++){
		ex[i]=0;
		ey[i]=.25;
		}

	cout<<"errore "<<gr2->GetErrorY(5)<<endl;
	gr2->Fit("f1");
	gr2->Draw("AP");


    Grafica->Run("");
	return 0;
	}
