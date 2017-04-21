/*
Scaricate i file che contengono i risultati di un ipotetico
esperimento di conteggio segnale+fondo
- data_funzione.txt
- data_sidebands.txt

Scoprite quali sono i segnali in essi celati, cioè trovate:
- I valori di ascissa su cui sono centrati i picchi e la loro larghezza
(sigma gaussiana)
- Il numero di eventi di segnale contenuti nei picchi

Si sa inoltre che i picchi attesi sono di forma gaussiana, mentre il
fondo concorrente all'osservazione del segnale segue una
distribuzione parabolica, nel primo caso, ed esponenziale nel
secondo.

compile with:

c++ ../Code/fit.cpp ../../labII.cc -o fit.o `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TApplication.h>
#include "../../labII.h"


int main(){

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);

	//-------------- SIGNAL + BACKGROUND -----------------
	
	//preparare istogramma
	int nbins_funzione = 100;
	TH1F* histo_funzione = makeTH1F_file("../data_funzione.txt", "Funzione", nbins_funzione);

	//fit segnale + fondo
	TF1* funzione = new TF1("funzione", "gaus(0)+[3]*x*x+[4]*x+[5]");
	funzione->SetParameter(0, 4000);
	funzione->SetParameter(1, 5);
	funzione->SetParameter(2, histo_funzione->GetRMS());
	funzione->SetParameter(3, -40);
	funzione->SetParameter(4, 400);
	funzione->SetParameter(5, 8500);

	TCanvas* c1 = new TCanvas("funzione");
	histo_funzione->Fit("funzione", "L");
	histo_funzione->Draw();

	//estrarre segnale e ottenere parametri
	TF1* signal = new TF1("signal", "gaus");
	signal->SetParameter(0, funzione->GetParameter(0));
	signal->SetParameter(1, funzione->GetParameter(1));
	signal->SetParameter(2, funzione->GetParameter(2));

	std::cout << "-------- DATA FUNZIONE ------- \n" << 
			"\nValore di ascissa su cui è centrato il picco: " << funzione->GetParameter(1) <<
			"\nLarghezza picco: " << funzione->GetParameter(2) << std::endl;

	//numero di eventi di segnale contenuti nei picchi
	double nSignal = (histo_funzione->GetXaxis()->GetBinWidth(1))
					 *signal->Integral(histo_funzione->GetXaxis()->GetBinCenter(1), 
									  histo_funzione->GetXaxis()->GetBinCenter(nbins_funzione));

	std::cout << "Numero eventi di segnale nel picco: " << nSignal << std::endl;
	

	

	//------------------- SIDEBANDS ------------------

	int nbins_sidebands = 200;

	TH1F* histo_sidebands = makeTH1F_file("../data_sidebands.txt", "Sidebands", nbins_sidebands);

	//fit di regione con la funzione che parametrizza il fondo
	TF1* fsidebands = new TF1("fsidebands", "expo");
	
	TCanvas* c2 = new TCanvas("sidebands");
	c2->Divide(0,2);
	c2->cd(1);
	histo_sidebands->Fit("fsidebands", "", "", 0, 100);
	histo_sidebands->Draw();


	TH1F* sidebands_signal = new TH1F("sidebands signal",
									  "sidebands signal",
									  nbins_sidebands,
									  histo_sidebands->GetXaxis()->GetBinCenter(1),
									  histo_sidebands->GetXaxis()->GetBinCenter(nbins_sidebands));


	//sottrarre al contenuto di ciascun bin dell'istogramma il valore della
	//funzione calcolata nel centro del bin
	for(int i=1; i<nbins_sidebands; i++)
	{
		double originalcontent = histo_sidebands->GetBinContent(i);
		double backgroundvalue = fsidebands->Eval(histo_sidebands->GetXaxis()->GetBinCenter(i));
		sidebands_signal->SetBinContent(i, originalcontent - backgroundvalue);
	}

	//fit due gaussiane
    TF1* signalfit = new TF1("signalfit", "gaus(0) + gaus(3)");
    //signalfit->SetParameter(0, );
    signalfit->SetParameter(1, 130);
    signalfit->SetParameter(2, 1);
    //signalfit->SetParameter(3, );
    signalfit->SetParameter(4, 170);
    signalfit->SetParameter(5, 10);

    c2->cd(2);
	sidebands_signal->Fit("signalfit", "", "", 100, 200);
	sidebands_signal->Draw();


    std::cout << "-------- DATA FUNZIONE ------- \n" << 
			"\nValore di ascissa su cui è centrato il picco 1: " << signalfit->GetParameter(1) <<
			"\nLarghezza picco 1: " << signalfit->GetParameter(2) <<
			"\nValore di ascissa su cui è centrato il picco 2: " << signalfit->GetParameter(4) <<
			"\nLarghezza picco 2: " << signalfit->GetParameter(5) << std::endl;;

	//numero di eventi di segnale contenuti nei picchi
	double nSignal_sidebands = (sidebands_signal->GetXaxis()->GetBinWidth(1))
					 *signalfit->Integral(sidebands_signal->GetXaxis()->GetBinCenter(1), 
									  sidebands_signal->GetXaxis()->GetBinCenter(nbins_sidebands));

	std::cout << "Numero eventi di segnale nei picchi: " << nSignal_sidebands << std::endl;



	Grafica->Run();
	return 0;
}