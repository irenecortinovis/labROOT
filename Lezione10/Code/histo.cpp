/*

Scrivere un programma che leggendo i dati dal file Histo_data.txt , riempia
un istogramma con il metodo Fill o con il metodo SetBinContent.
L'istogramma deve avere estremi min e max definiti come il valore minore e quello
maggiore tra i dati letti.
Fittare l'istogramma con la somma di due gaussiane

compile with:

c++ ../Code/histo.cpp ../../labII.cc -o histo.o `root-config --cflags --glibs`

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TF1.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TApplication.h>
#include "../../labII.h"



int main(){

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);

	TH1F* histo = makeTH1F_file("../Histo_data.txt", "My histogram", 100);

	//create the TF1 for fit: two gaussians
	TF1* f1 = new TF1("f1", "gaus(0)+gaus(3)", histo->GetMinimumStored(), histo->GetMaximumStored());
	//create parameters for f1
	int Nestrazioni1 = 50, Nestrazioni2 = 10;
	double mean1 = -1.1, mean2 = 0.5, sigma1 = 0.3, sigma2 = 0.3;
	f1->SetParameters(Nestrazioni1, mean1, mean2, Nestrazioni2, sigma1, sigma2);
	
	//fit TH1F with likelihood
	histo->Fit("f1", "L");

	//draw the TH1F
	TCanvas* c1 = new TCanvas("My canvas");
	histo->Draw();

	Grafica->Run();

	return 0;
}