/*
This program show the difference between the tstudent and the gaussian
ditribution

compile with:
c++ -o student student-gauss.cpp `root-config --cflags --glibs`

current version
./student 20

this allows
for i in `seq 10 100`; do ./student $i; done

fixed `int normal_sample_dimension = 100 ;` version
./student

references
https://en.wikipedia.org/wiki/Student%27s_t-distribution
https://en.wikipedia.org/wiki/Bessel%27s_correction

ACHTUNG! if normal_sample_dimension tends to infinity, the tstudent
distribution tends to a standard normal distribution
i.e. with expected value 0. and stdev 1.

*/


#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <TSystem.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom.h>
#include <TRandom3.h>

double const pi=3.1415926535897;

//returns a random number from uniform distribution between min and max
// too slow, using TRandom3 instead, reference here:
// https://root.cern.ch/doc/master/testrandom_8C.html
/*
double rand_range(double min, double max){
	return min + (max - min) * rand() / (RAND_MAX);
}


//gauss function
double f_gaus(double x, double *par){
	return 1/sqrt(2*pi*par[1]*par[1]) * exp(-1*(x-par[0])*(x-par[0])/(2*par[1]*par[1]));
}

//generate random numbers with try and catch method
double rand_TryAndCatch(double f(double, double*), double *par, double xMin, double xMax,
				double yMin, double yMax){
	double x = 0.;
	double y = 0.;
	do
	{
		x = rand_range(xMin, xMax);
		y = rand_range(yMin, yMax);
	} while (y > f(x, par));

	return x;
}
*/

int main(int numArg, char** listArg){

	// TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	gSystem->Load("libMathMore");

	// shows more info on the graph about the fit
	gStyle->SetOptFit(1111);

	// number of random numbers ditributed as a gaussian ditribution
	std::string::size_type sz;
	int normal_sample_dimension = std::stoi(listArg[1], &sz) ;
	// int normal_sample_dimension = 100 ;
	double mu = 1. ;
	double stdev = 2. ;
	// how many time a set of random numbers ditributed as a gaussian
	// of cardinality normal_sample_dimension is extracted
	int tstd_sample_dimension = 10000 ;
	// min and max of the t Student ditribution
	double tstd_xmin = -4. ;
	double tstd_xmax = 4. ;
	//min and max of the standard normal distribution
	double std_norm_xmin = -4. ;
	double std_norm_xmax = 4. ;

	TH1F* histo_gauss = new TH1F("gauss standard", "gauss standard", tstd_sample_dimension / 100, std_norm_xmin, std_norm_xmax);
	TH1F* histo_tstd = new TH1F("tstd standard", "tstd standard", tstd_sample_dimension / 100 , tstd_xmin, tstd_xmax);

	TRandom *r3 = new TRandom3() ;
	r3->SetSeed();

	for (int i=0; i<tstd_sample_dimension; i++) {
		double normal_rand = 0. ;
		double sum = 0. ;
		double sumsqrd = 0. ;
		for (int j=0; j<normal_sample_dimension; j++){
			// too slow, using TRandom3 instead
			// normal_rand = rand_TryAndCatch(f_gaus, gauss_par, -2*stdev, 2*stdev, 0, 1) ;
			normal_rand = r3 -> Gaus(mu,stdev) ;
			sum += normal_rand ;
			sumsqrd += normal_rand*normal_rand ;
		}
		double samplemu = (double) sum / normal_sample_dimension ;
		double samplestdev = sqrt ( (double) sumsqrd / (normal_sample_dimension - 1.) - (double) sum*sum / (normal_sample_dimension - 1. ) / normal_sample_dimension ) ;
		double gauss_point = (samplemu - mu) / stdev * sqrt (normal_sample_dimension) ;
		double tstd_point = (samplemu - mu ) / samplestdev * sqrt(normal_sample_dimension) ;

		histo_gauss->Fill(gauss_point) ;
		histo_tstd->Fill(tstd_point) ;

		// std::cout << normal_set_array[i].gauss << std::endl ;
		// std::cout << normal_set_array[i].tstd << std::endl ;

	}

	//provo con quella di root
	TF1* pdfStudent = new TF1("pdfStudent", "ROOT::Math::tdistribution_pdf(x,[0])", tstd_xmin,tstd_xmax);
   	pdfStudent->SetParameter(0,normal_sample_dimension - 1);

   	TCanvas *c1 = new TCanvas("tstd-canvas", "student distribution - t student", 10, 10, 1000, 800);
	histo_tstd->SetTitle("Student Dtribution - t Student");
	histo_tstd->Scale(1./histo_tstd->Integral(), "width");
	histo_tstd->Draw();
	histo_tstd->Fit("pdfStudent", "Q");
	double tstd_chi_sqrd_reduced = histo_tstd->GetFunction("pdfStudent")->GetChisquare() / histo_tstd->GetFunction("pdfStudent")->GetNDF() ;


	TCanvas *c2 = new TCanvas ("tstd-canvas-fit-gauss", "student ditribution - gauss", 10, 10, 1000, 800) ;
	TH1F* histo_tstd_gauss_fit = (TH1F*) histo_tstd->Clone() ;
	histo_tstd_gauss_fit->SetTitle("Student Distribution - gauss") ;
	histo_tstd_gauss_fit->Draw();
	histo_tstd_gauss_fit->Fit("gaus","Q");
	double gaus_chi_sqrd_reduced = histo_tstd_gauss_fit->GetFunction("gaus")->GetChisquare() / histo_tstd_gauss_fit->GetFunction("gaus")->GetNDF() ;

/*
	// check that the gauss istogram is actually different
	TCanvas *c3 = new TCanvas("gauss-histo", "Gauss Distribution", 10, 10, 1000, 800);
	histo_gauss->Scale(1./histo_gauss->Integral(), "width");
	histo_gauss->Draw();
	histo_gauss->Fit("gaus","Q");
*/

	std::cout << "N = " << normal_sample_dimension ;
//	std::cout << tstd_chi_sqrd_reduced << std::endl ;
//	std::cout << gaus_chi_sqrd_reduced << std::endl ;
	if (tstd_chi_sqrd_reduced < gaus_chi_sqrd_reduced)
		std::cout << " , better tSt ," ;
	else
		std::cout << " , better gaus ," ;
	std::cout << " chi(tstd) / chi(gauss) = " << tstd_chi_sqrd_reduced / gaus_chi_sqrd_reduced << std::endl ;

	c1->Print(Form("%d-tstd-fit-tstd.png", normal_sample_dimension), "png") ;
	c2->Print(Form("%d-tstd-fit-gauss.png", normal_sample_dimension), "png") ;

	// Grafica->Run();


	return 0;
}
/*

Si nota che con N fino a 20 regge forte e salda la t student,
sopra il chisqrd oscilla attorno al 95%-105% a favore dell'una o
dell'altra, a seconda di boh, gli astri

N = 10 , better tSt , chi(tstd) / chi(gauss) = 0.579558
N = 11 , better tSt , chi(tstd) / chi(gauss) = 0.793885
N = 12 , better tSt , chi(tstd) / chi(gauss) = 0.705278
N = 13 , better tSt , chi(tstd) / chi(gauss) = 0.647397
N = 14 , better tSt , chi(tstd) / chi(gauss) = 0.76319
N = 15 , better tSt , chi(tstd) / chi(gauss) = 0.686373
N = 16 , better tSt , chi(tstd) / chi(gauss) = 0.771766
N = 17 , better tSt , chi(tstd) / chi(gauss) = 0.840434
N = 18 , better tSt , chi(tstd) / chi(gauss) = 0.807928
N = 19 , better tSt , chi(tstd) / chi(gauss) = 0.761673
N = 20 , better tSt , chi(tstd) / chi(gauss) = 0.794411
N = 21 , better gaus , chi(tstd) / chi(gauss) = 1.08408
N = 22 , better tSt , chi(tstd) / chi(gauss) = 0.953363
N = 23 , better tSt , chi(tstd) / chi(gauss) = 0.936169
N = 24 , better tSt , chi(tstd) / chi(gauss) = 0.846197
N = 25 , better tSt , chi(tstd) / chi(gauss) = 0.953442
N = 26 , better tSt , chi(tstd) / chi(gauss) = 0.938187
N = 27 , better tSt , chi(tstd) / chi(gauss) = 0.914834
N = 28 , better tSt , chi(tstd) / chi(gauss) = 0.996198
N = 29 , better tSt , chi(tstd) / chi(gauss) = 0.968164
N = 30 , better tSt , chi(tstd) / chi(gauss) = 0.939049
N = 31 , better tSt , chi(tstd) / chi(gauss) = 0.964448
N = 32 , better tSt , chi(tstd) / chi(gauss) = 0.949578
N = 33 , better tSt , chi(tstd) / chi(gauss) = 0.940001
N = 34 , better tSt , chi(tstd) / chi(gauss) = 0.922198
N = 35 , better tSt , chi(tstd) / chi(gauss) = 0.910627
N = 36 , better gaus , chi(tstd) / chi(gauss) = 1.00144
N = 37 , better tSt , chi(tstd) / chi(gauss) = 0.976439
N = 38 , better gaus , chi(tstd) / chi(gauss) = 1.007
N = 39 , better tSt , chi(tstd) / chi(gauss) = 0.962141
N = 40 , better tSt , chi(tstd) / chi(gauss) = 0.995954
N = 41 , better tSt , chi(tstd) / chi(gauss) = 0.98309
N = 42 , better gaus , chi(tstd) / chi(gauss) = 1.0068
N = 43 , better gaus , chi(tstd) / chi(gauss) = 1.0044
N = 44 , better tSt , chi(tstd) / chi(gauss) = 0.975807
N = 45 , better tSt , chi(tstd) / chi(gauss) = 0.97544
N = 46 , better gaus , chi(tstd) / chi(gauss) = 1.00338
N = 47 , better tSt , chi(tstd) / chi(gauss) = 0.989366
N = 48 , better tSt , chi(tstd) / chi(gauss) = 0.960803
N = 49 , better tSt , chi(tstd) / chi(gauss) = 0.981221
N = 50 , better tSt , chi(tstd) / chi(gauss) = 0.975954
N = 51 , better gaus , chi(tstd) / chi(gauss) = 1.0091
N = 52 , better tSt , chi(tstd) / chi(gauss) = 0.990712
N = 53 , better gaus , chi(tstd) / chi(gauss) = 1.00511
N = 54 , better tSt , chi(tstd) / chi(gauss) = 0.995851
N = 55 , better tSt , chi(tstd) / chi(gauss) = 0.986189
N = 56 , better tSt , chi(tstd) / chi(gauss) = 0.990864
N = 57 , better tSt , chi(tstd) / chi(gauss) = 0.98726
N = 58 , better gaus , chi(tstd) / chi(gauss) = 1.00275
N = 59 , better gaus , chi(tstd) / chi(gauss) = 1.0356
N = 60 , better tSt , chi(tstd) / chi(gauss) = 0.993198
N = 61 , better tSt , chi(tstd) / chi(gauss) = 0.980195
N = 62 , better tSt , chi(tstd) / chi(gauss) = 0.9954
N = 63 , better tSt , chi(tstd) / chi(gauss) = 0.992274
N = 64 , better tSt , chi(tstd) / chi(gauss) = 0.931958
N = 65 , better gaus , chi(tstd) / chi(gauss) = 1.0133
N = 66 , better gaus , chi(tstd) / chi(gauss) = 1.00232
N = 67 , better tSt , chi(tstd) / chi(gauss) = 0.991062
N = 68 , better gaus , chi(tstd) / chi(gauss) = 1.00621
N = 69 , better tSt , chi(tstd) / chi(gauss) = 0.951123
N = 70 , better tSt , chi(tstd) / chi(gauss) = 0.982123
N = 71 , better tSt , chi(tstd) / chi(gauss) = 0.998431
N = 72 , better gaus , chi(tstd) / chi(gauss) = 1.00128
N = 73 , better gaus , chi(tstd) / chi(gauss) = 1.01648
N = 74 , better gaus , chi(tstd) / chi(gauss) = 1.0094
N = 75 , better gaus , chi(tstd) / chi(gauss) = 1.039
N = 76 , better tSt , chi(tstd) / chi(gauss) = 0.988456
N = 77 , better gaus , chi(tstd) / chi(gauss) = 1.00073
N = 78 , better gaus , chi(tstd) / chi(gauss) = 1.01326
N = 79 , better gaus , chi(tstd) / chi(gauss) = 1.01533
N = 80 , better tSt , chi(tstd) / chi(gauss) = 0.960408
N = 81 , better tSt , chi(tstd) / chi(gauss) = 0.979922
N = 82 , better tSt , chi(tstd) / chi(gauss) = 0.96605
N = 83 , better tSt , chi(tstd) / chi(gauss) = 0.954665
N = 84 , better tSt , chi(tstd) / chi(gauss) = 0.944947
N = 85 , better gaus , chi(tstd) / chi(gauss) = 1.02469
N = 86 , better tSt , chi(tstd) / chi(gauss) = 0.990486
N = 87 , better gaus , chi(tstd) / chi(gauss) = 1.04508
N = 88 , better tSt , chi(tstd) / chi(gauss) = 0.972362
N = 89 , better gaus , chi(tstd) / chi(gauss) = 1.01336
N = 90 , better tSt , chi(tstd) / chi(gauss) = 0.98769
N = 91 , better tSt , chi(tstd) / chi(gauss) = 0.975635
N = 92 , better tSt , chi(tstd) / chi(gauss) = 0.99529
N = 93 , better gaus , chi(tstd) / chi(gauss) = 1.04862
N = 94 , better tSt , chi(tstd) / chi(gauss) = 0.99401
N = 95 , better gaus , chi(tstd) / chi(gauss) = 1.03628
N = 96 , better tSt , chi(tstd) / chi(gauss) = 0.994073
N = 97 , better tSt , chi(tstd) / chi(gauss) = 0.998215
N = 98 , better gaus , chi(tstd) / chi(gauss) = 1.0106
N = 99 , better tSt , chi(tstd) / chi(gauss) = 0.965786
N = 100 , better gaus , chi(tstd) / chi(gauss) = 1.03022

*/
