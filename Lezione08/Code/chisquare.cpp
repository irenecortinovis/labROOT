/*
Codificare la pdf chi2 in un TF1 e scrivere un programma che la disegna
per un numero dato di gradi di libertà

compile with:
c++ ../../labII.cc ../Code/chisquare.cpp -o chisquare.o `root-config --cflags --glibs`

*/

#include <iostream>
#include <math.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include "../../labII.h"

int main(){
	
	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	int gdl = 100;

	TCanvas* c1 = new TCanvas("c1", "Il mio canvas");
	chi2_PDF(gdl)->Draw();

	Grafica->Run();

	return 0;
}