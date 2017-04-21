
/*
compile with:
c++ -o histogram.o ../Code/histogram.cpp ../../labII.cc `root-config --cflags --glibs`
*/

#include "../../labII.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <TH1F.h>
#include <TCanvas.h>

int main(){

	srand(time(NULL));
	double min = -1;
	double max = 1;
	double mean;
	int nEstractions = 10;
	int N = 10000;

	TH1F pdf("name", "title", 100, min, max);

	for(int i=0; i<N; i++)
	{
		mean = 0;
		for(int j=0; j<nEstractions; j++)
		{
			mean += rand_range(min, max);
		}
		mean /= (double) nEstractions;
		pdf.Fill(mean);
	}

	TCanvas cnv;
	pdf.Draw();
	pdf.Fit("gaus");
	cnv.Print("istogramma.png", "png");

	return 0;
}