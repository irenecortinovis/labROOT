/*
compile with:
c++ -o lightspeed.o lightspeed.cpp `root-config --glibs --cflags`
*/


#include <iostream>
#include <cmath>
#include <TRandom.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>
	


int main()
{
	TApplication* Grafica = new TApplication("Grafica", 0, NULL);

	//trandom variables
	TRandom *rndw = new TRandom();	
    TRandom *rnds = new TRandom();

    double randgaus_w;
    double randgaus_s;
    double c2;

	//mean, sigma
	double par_w[2] = {1040, 10};
	double par_s[2] = {30, 7};
	//estimators for mean, sigma, std error
	double est_par_w[3];
	double est_par_s[3];
	//c1, errc1
	double c1_par[2];
	//c2, errc2, std error
	double c2_par[3];

	//number of measures in each experiment
	int num = 50;
	//number of experiments
	int n_repetitions = 10000;

	//prepare histograms
	int nbin = 200;

	TH1F* histow = new TH1F("w mean", "w mean", nbin, 1034, 1046);
	TH1F* histos = new TH1F("s mean", "s mean", nbin, 25, 35);
	TH1F* histoc1 = new TH1F("c1 mean", "c1 mean", nbin, 25, 45);
	TH1F* histoc2 = new TH1F("c2 mean", "c2 mean", nbin, 25, 45);
	TH1F* histoerrc1 = new TH1F("err c1", "err c1", nbin, 0, 10);
	TH1F* histoerrc2 = new TH1F("err c2", "err c2", nbin, 0, 10);


	//loop on n of experiments
	for(int i=0; i<n_repetitions; i++)
	{
		//variables to calculate mean and sigma
		double sum_w = 0;
		double sum2_w = 0;

		double sum_s = 0;
		double sum2_s = 0;

		double sum_c2 = 0;
		double sum2_c2 = 0;

		//loop on measures in each experiment
		for(int i=0; i<num; i++)
		{
			randgaus_w = rndw->Gaus(par_w[0], par_w[1]);
			sum_w += randgaus_w;
			sum2_w += randgaus_w*randgaus_w;

			randgaus_s = rnds->Gaus(par_s[0], par_s[1]); 
			sum_s += randgaus_s;
			sum2_s += randgaus_s*randgaus_s;

			c2 = randgaus_w / randgaus_s;
			sum_c2 += c2;
			sum2_c2 += c2*c2;
		}

		//compute mean, sigma, std error of mean for w
		est_par_w[0] = sum_w/num;
		est_par_w[1] = sum2_w/num - est_par_w[0]*est_par_w[0];
		est_par_w[2] = sqrt(est_par_w[1] / (num-1));

		//compute mean, sigma, std error of mean for s
		est_par_s[0] = sum_s/num;
		est_par_s[1] = sum2_s/num - est_par_s[0]*est_par_s[0];
		est_par_s[2] = sqrt(est_par_s[1] / (num-1));

		//c1 and errc1 (uncertainty propagation)
		c1_par[0] = est_par_w[0] / est_par_s[0];
		c1_par[1] = sqrt(pow((est_par_w[2]/est_par_s[0]),2)
						+ pow((est_par_w[0]*est_par_s[2]/pow(est_par_s[0],2)),2));

		//c2 and errc2
		c2_par[0] = sum_c2/num;
		c2_par[1] = sum2_c2/num - c2_par[0]*c2_par[0];
		c2_par[2] = sqrt(c2_par[1] / (num-1));

		//fill histograms
		histow->Fill(est_par_w[0]);
		histos->Fill(est_par_s[0]);
		histoc1->Fill(c1_par[0]);
		histoc2->Fill(c2_par[0]);
		histoerrc1->Fill(c1_par[1]);
		histoerrc2->Fill(c2_par[2]);
	}

	//draw histograms

	gStyle->SetOptFit(1111);

	TCanvas* canvas1 = new TCanvas("c2");
	canvas1->Divide(2,3);
	
	canvas1->cd(5);
	histow->Draw();
	histow->Fit("gaus", "L");
	
	canvas1->cd(6);
	histos->Draw();
	histos->Fit("gaus", "L");
	
	canvas1->cd(1);
	histoc1->Draw();
	histoc1->Fit("gaus", "L");

	canvas1->cd(2);
	histoerrc1->Draw();

	canvas1->cd(3);
	histoc2->Draw();
	histoc2->Fit("gaus", "L");

	canvas1->cd(4);
	histoerrc2->Draw();


	//run TApplication
	Grafica->Run();



	return 0;
}