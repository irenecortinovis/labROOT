#include <iostream>
#include <ctime>
#include <cmath>
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TApplication.h"
#include "TMath.h"
#include "TGraph.h"
#include "TStyle.h"
#include <string>

using namespace std;
//
// c++ -o likelihood.o ../Code/likelihood.cpp `root-config --cflags --glibs`



int O[] = { 1, 3, 4, 5, 3, 2, 1, 1, 0, 0 };
//int O[] = { 1, 3, 4, 5, 3, 2, 0, 0, 1, 1 };
int s = sizeof(O) / sizeof(O[0]);
int N = s - 1;

int sommatoria(int array[], int size) {
	if (size <= 0) return -1;
	int cursum = 0;
	for (int i = 0; i < size; ++i) {
		cursum += array[i];
	}
	return cursum;
}

int I = sommatoria(O, s);

int fact(int n) {
	if (n <= 1) return 1;
	return fact(n-1) * n;
}

double likelihood(double mu, int n, int freq) {
	double val = exp(-mu) * pow(mu, n);
	val /= fact(n);
	val = pow(val, freq);
	return val;
}

double func_likelihood(double mu) {
	double l = 1;
	for (int n = 0; n < s; ++n) {
		l *= likelihood(mu, n, O[n]);
	}
	return log(l);
}

double max_trisezione(double x0, double x1, double precision) {
	if ((fabs(x1 - x0)) < precision) return 0.5 * (x0 + x1);
	double x2 = x0 + ((x1 - x0) / 3.);
	double x3 = x1 - ((x1 - x0) / 3.);
	if (func_likelihood(x2) < func_likelihood(x3)) return max_trisezione(x2, x1, precision);
	else return max_trisezione(x0, x3, precision);
}

double errori(double mu, const double muhat) {
    double val = func_likelihood(mu);
    val -= func_likelihood(muhat);
    val += 0.5;
    return val;
}

double zero_R_bisezione(const double muhat, double xMin, double xMax, double precision) {
	double x_m = 0.5 * (xMin + xMax);
	if ((xMax - xMin) < precision) return x_m;
	if (errori(x_m, muhat) * errori(xMin, muhat) < 0) {
		return zero_R_bisezione(muhat, xMin, x_m, precision);
	}
	return zero_R_bisezione(muhat, x_m, xMax, precision);
}

double integrale_rettangoli(double xMin, double xMax, int N_bin) {
	double step = (xMax - xMin) / double(N_bin);
	double integrale = 0;
	double x = xMin;
	while (x < xMax) {
		double h = exp(func_likelihood(0.5 * (x + x + step)));
		integrale += h * step;
		x += step;
	}
	return integrale;
}

double poissonf(double *x, double *par) {
	return par[0]*TMath::Poisson(x[0],par[1]);
}


int main() {
    
    TApplication *mine = new TApplication("mine", 0, 0);
	// Calcolo di media e deviazione standard
	double m = 0;
	for (int i = 0; i < s; ++i) {
		m += i * O[i];
	}
	m /= I;

	double mediaScarti = 0;
	for (int i = 0; i < s; ++i) {
		mediaScarti += O[i] * pow(i - m, 2);
	}
	mediaScarti /= (I-1);
	double sigma = sqrt(mediaScarti);

	// media calcolata con maximum likelihood
	double ml = max_trisezione(0, N, 0.000001);

	// calcolo errore destro e errore sinistro
	double mum = zero_R_bisezione(ml, 0, ml, 0.000001);
	double mup = zero_R_bisezione(ml, ml, N, 0.000001);
	double es = ml - mum;
	double ed = mup - ml;

	// calcolo del chi quadro, ignorando i bin con frequenza 0
	double chi1 = 0;
	for (int n = 0; n < s; ++n) {
		if (O[n] != 0) {
			double expected = likelihood(ml, n, 1);
			double val = O[n] - I*expected;
			val = pow(val, 2);
			val /= O[n];
			chi1 += val;
		}
	}

	// calcolo del chi quadro, con errore 1 per i bin con frequenza 0
	double chi2 = 0;
	for (int n = 0; n < s; ++n) {
		double expected = likelihood(ml, n, 1);
		double val = O[n] - I*expected;
		val = pow(val, 2);
		if(O[n] != 0) val /= O[n];
		if(O[n] == 0) val /= 1;
		chi2 += val;
	}

	// Probabilita' che l'esperimento dia un risultato compreso tra mu- e mu+
	double p = integrale_rettangoli(mum, mup, 1000);
        p /= integrale_rettangoli(0, s, 1000);

        // Stampa dei dati del problema
        cout << endl << endl;
        cout << "RISULTATI:" << endl;
        cout << "Frequenza dei conteggi:                               \t O = [";
        for (int i = 0; i < s; ++i) {
                cout << O[i];
                if (i != s-1) cout << ", ";
        }
        cout << "]" << endl;
        cout << endl;
        cout << "Massimo conteggio considerato:                        \t N = " << N << endl;
        cout << "Numero totale di osservazioni:                        \t I = " << I << endl;
        cout << "Media pesata:                                         \t m = " << m << endl;
        cout << "Deviazione standard:                                  \t sigma = " << sigma << endl;
	cout << endl;
	cout << "Media likelihood:                                     \t ml = " << ml << endl;
	cout << "ML - Errore sinistro:                                 \t es = " << es << endl;
	cout << "ML - Errore destro:                                   \t ed = " << ed << endl;
        cout << endl;
	cout << "Chi quadro 1 (7 d.o.f.):                              \t chi = " << chi1 << " errore sperim., no bin con freq. 0" << endl;
	cout << "Chi quadro 2 (9 d.o.f.):                              \t chi = " << chi2 << " errore sperim., =1 per bin con freq. 0" << endl;
	cout << endl;
	cout << "ML - Probabilita':                                    \t p = " << p << endl;
        cout << "ML - Gaussiana 1 sigma                                \t p = 0.68268 " << endl;
	cout << endl;

	// Disegno dell'istogramma
	TH1F *histo = new TH1F("histo", "osservazioni+gaussiana", s, -0.5, s-0.5);
	TH1F *histo1 = new TH1F("histo", "osservazioni+poissoniana", s, -0.5, s-0.5);
	for (int i = 0; i < s; ++i) {
		histo->Fill(i, O[i]);
		histo1->Fill(i, O[i]);
	}

    gStyle->SetOptFit(1111);
	// Fit con gaussiana
	TCanvas *c1 = new TCanvas();
    histo->Draw("hist");
	TF1* gauss = new TF1("gauss", "gaus", 0, s);
	gauss->SetParameter(1, m);
	gauss->SetParameter(2, m);
    histo->SetFillColor(4);
	histo->Fit("gauss", "L");
    gauss->Draw("same");
    c1->Update();

	// Fit con poissoniana
	TCanvas *c2 = new TCanvas();
    histo1->Draw("hist");
	TF1* pois = new TF1("pois", poissonf, 0, s, 2);
	pois->SetParameter(0, I);
	pois->SetParameter(1, m);
    histo1->SetFillColor(5);
	histo1->Fit("pois", "L");
    pois->Draw("same");

        // plot del nostro risultato (in nero), usando la funzione P=(e^ml)*(ml^x)/Gamma(x+1)
        //  che e' la distribuzione di Poisson generalizzata a variabile continua (x al posto di n)
        double *xg = new double[s*10];
        double *yg = new double[s*10];
        for (int i = 0; i < s*10; ++i) {
                xg[i] = i/10.;
                yg[i] = I*exp(-ml)*pow(ml, xg[i])/TMath::Gamma(xg[i]+1);
        }
        TGraph *gr1 = new TGraph(s*10, xg, yg);
        gr1->SetLineColor(1);
        gr1->SetLineWidth(2);
        gr1->Draw("same");
    c2->Update();

    mine->Run();
    return 0;
}