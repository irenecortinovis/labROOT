/*
compile with:
c++ ../Code/likelihood.cpp ../../labII.cc -o likelihood.o `root-config --cflags --glibs`
*/




#include <iostream>
#include <math.h>
#include <TH1F.h>
#include <TApplication.h>
#include <TCanvas.h>
#include "../../labII.h"

int sommatoria(int array[], int size)
{
	if(size<=0) return -1;
	int cursum = 0;
	for(int i=0; i<size; ++i)
	{
		cursum += array[i];
	}
	return cursum;
}

//recursive factorial
int factorial(int n)
{
	if (n<=1) return 1;
	return factorial(n-1)*n;
}

//produttoria
double likelihood(double mu, int n, int freq)
{
	double val = exp(-mu) * pow(mu,n);
	val /= factorial(n);
	val = pow(val,freq);
	return val
}

//likelihood
double func_likelihood(double mu, int array[])
{
	double l=1;
	for(int i=0; i<(sizeof(array)/sizeof(array[0])); i++)
	{
		l *= likelihood(mu, i, array[i]);
	}
	return log(l);
}

//trisection
double max_trisezione(double x0, double x1, double precision)
{
	if((fabs(x1-x0)) < precision) return 0.5*(x0+x1);
	double x2 = x0 + ((x1-x0)/3.);
	double x3 = x1 - ((x1-x0)/3.);
	if(func_likelihood(x2) < func_likelihood(x3))
		return max_trisezione(x2, x1, precision);
	else
		return max_trisezione(x0, x3, precision);
}





int main(){

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);

	int O[] = {1,3,4,5,3,2,1,1,0,0};
	int s = sizeof(O) / sizeof(O[0]);
	int N = s-1;

	//draw histogram
	TH1F* histo = new TH1F("histo", "observations", s, -0.5, s-0.5);
	for (int i=0; i<s; ++i)
	{
		histo->Fill(i, O[i]);
	}

	histo->SetFillColor(5);

	TCanvas* c1 = new TCanvas("observations");
	histo->Draw();

	//calculate mean and stdev
	int I = sommatoria(O, s);

	double m = 0;
	for(int i=0; i<s; i++)
	{
		m += i*O[i];
	}
	m /= I;

	double mediaScarti = 0;
	for (int i=0; i<s; i++)
	{
		mediaScarti += O[i] * pow(i-m,2);
	}
	mediaScarti /= (I-1);
	double sigma = sqrt(mediaScarti);

	//media calclata con maximum likelihood
	double ml = max_trisezione(0, N, 0.000001);

	std::cout << m << "\t" << ml << std::endl;




	Grafica->Run();

	return 0;
}