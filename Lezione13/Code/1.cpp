/*
compile with:
c++ ../Code/1.cpp -o 1.o `root-config --cflags --glibs`
*/


#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TGraph.h>

#include "lib.h"

#include <cmath>
#include <iostream>

using namespace std;

int cont [10] = {1, 3, 4, 5, 3, 2, 1, 1, 0, 0};
const int size = sizeof(cont) / sizeof(cont[0]);

int main ()
	{

	// CREAZIONE ISTOGRAMMA.

	//TApplication * app = new TApplication ("App", 0, 0);
	TCanvas canvas;

	TH1F isto ("isto", "Osservazioni", size, -0.5, size-0.5); 		// Per centrare i bin.

	for (int i = 0; i < size; i++)
		{
		isto.Fill (i, cont[i]);
		} 

	isto.Draw ();
	isto.SetFillColor (5);
	isto.SetLineColor (92);

	canvas.Print ("isto.png", "png");



	// CALCOLO MEDIA E VARIANZA CON FORMULE.

	double media = fmedia (cont, size);

	double sigma = fsigma (cont, size);

	cout << "media: " << media << endl << "sigma: " << sigma << endl;

	

	// CALCOLO MEDIA E VARIANZA CON LIKELIHOOD.

	double mediaL = tris (0, size, 0.000001, cont, size);

	cout << "mediaL: " << mediaL << endl;

	double mum = fsmazza (mediaL, 0, mediaL, 0.000001, cont, size);
	double mup = fsmazza (mediaL, mediaL, size, 0.000001, cont, size);
	double valmin = mediaL - mum;
	double valsup = mup - mediaL;

	cout << "valore compreso tra: " << valmin << " e " << valsup << endl;

	TCanvas can2;

	TGraph * grafo = new TGraph ();
	int punti = 100;
	double min = 1.5;
	double max = 5;
	for (int i = 0; i < punti; i++)
		{
		double x = min + i*(max - min)/100.;
		double y = exp(flikelihood (x, cont, size)); 
		grafo -> SetPoint (i, x, y);
		}
	grafo -> Draw ("APC");
	grafo -> SetLineWidth (3);
	grafo -> SetLineColor (92);
	can2.Print ("Like.png", "png");



	// CALCOLO DEL CHIQUADRO.

	// Ignorando i bin con frequenza nulla.

	double chi1 = 0;
	for (int n = 0; n < size; n++)
		{
		if (cont[n] != 0)
			{
			double asp = fformula (mediaL, n, 1);
			double val = cont[n] - (fsommatoria (cont, size))*asp;
			val = pow (val, 2);
			chi1 += val;
			}
		}
	cout << "Chi1: " << chi1 << endl;

	// Assegnando errore 1 ai bin con frequenza nulla.

	double chi2 = 0;
	for (int n = 0; n < size; n++)
		{
		double asp = fformula (mediaL, n, 1);
		double val = cont[n] - (fsommatoria (cont, size))*asp;
		val = pow (val, 2);
		if (cont[n] != 0) val /= cont[n];
		if (cont[n] == 0) val  /= 1;
		chi2 += val;
		}
	cout << "Chi2: " << chi2 << endl;



	// CALCOLO DELLA PROBABILITA'

	// probabilità che l'esperimento dia un valore compreso tra mum e mup:

	double prob = frettoli (mum, mup, cont, size);
	// devo normalizzarlo perché la Likelihood non è di per sé normalizzata.
	prob /= frettoli (0, size, cont, size);

	cout << "Probabilità che l'esperimento dia un valore compreso tra mum e mup: " << prob << " %" <<endl;



	// FIT DEI DATI

	// Fit con Gaussiana

	TCanvas canG;
	TF1 * gauss = new TF1 ("gauss", "gaus", 0, size);
	gauss -> SetParameter (1, media);
	gauss -> SetParameter (2, media);
	gauss -> SetLineColor (kGray);
	isto.Fit ("gauss", "L");
	isto.Draw ();
	canG.Print ("conGauss.png", "png");

	// Fit con Poissoniana

	TCanvas canP;
	TF1 * pois = new TF1 ("pois", fpois, 0, size, 2);
	pois -> SetParameter (0, fsommatoria (cont, size));
	pois -> SetParameter (1, media);
	pois -> SetLineColor (kGray);
	isto.Fit ("pois", "L");
	isto.Draw ();
	canP.Print ("conPoisson.png", "png");
	

	//app -> Run ();


	return 0;
	}
