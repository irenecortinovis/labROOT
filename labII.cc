#include "labII.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
#include <algorithm>
#include "TF1.h"
#include "TH1F.h"


/*
to initialise TApplication:
TApplication* Grafica = new TApplication("Grafica", 0, NULL);
Grafica->Run();
*/

//	srand(time(NULL));
double rand_range(double min, double max){
	return min + (max - min) * rand() / (RAND_MAX);
}

//problem with min and max, because of int rounding
int rand_range(int min, int max){
	return round((double) (min + (max - min)) * rand() / (1.0 * RAND_MAX));
}

//gauss function
double f_gaus(double x){
	double mean = 0;
	double stdev = 0.5;
	return 1/sqrt(2*M_PI*stdev*stdev) * exp(-1*(x-mean)*(x-mean)/(2*stdev*stdev));
}

//generate random numbers with try and catch method
double rand_TryAndCatch(double f(double), double xMin, double xMax,
				double yMin, double yMax){
	double x = 0.;
	double y = 0.;

	do
	{
		x = rand_range(xMin, xMax);
		y = rand_range(yMin, yMax);
	} while (y > f(x));

	return x;
}


//recursive bisection algorithm
double bisectionRecursive(double f(double), double xMin,
						  double xMax, double precision){
	double x_m = 0.5 * (xMin + xMax);
	
	if ((xMax - xMin) < precision)
		return x_m;
	
	if (f(xMin) * f(x_m) < 0)
		return bisectionRecursive(f, xMin, x_m, precision);

	else
		return bisectionRecursive(f, x_m, xMax, precision);
}


//montecarlo numerical integration
double integral_montecarlo(double f(double), double xMin, double xMax,
						   double yMin, double yMax, int max_num){
	int n_integral = 0;
	for (int i=0; i<max_num; i++)
	{
		double x = rand_range(xMin, xMax);
		double y = rand_range(yMin, yMax);
		if (y < f(x))
			++n_integral;
	}
	return (yMax - yMin) * (xMax - xMin) * n_integral / max_num;
}


//riemann (rectangles) numerical integration
double integral_riemann(double f(double), double xMin, double xMax, double nBins){
	double step = (xMax-xMin) / nBins;
	double integral = 0;
	double x = xMin;
	for(int i=0; i<nBins; i++)
	{
		double y = (f(x)+f(x+step))/2;
		integral += y * step;
		x += step;
	}
	return integral;
}


//inverse function generator
/*
f(x), [a,b] given
calculate cumulative function: F(x) = integral of f(s)ds from a to x 
calculate inverse function: x = F^{-1}(y)
generate random numbers: random = F^{-1}(rand_range[a,b])
*/


/*
opens file (checking)
calculates n of entries, mean, error of mean
saves them in array 
closes file and returns array
*/
double* data_analysis(const char* path)
{
	double * values = new double[3];

	//open file
	std::ifstream infile;
	infile.open(path, std::ios::in);
	//check if it is good
	if(infile.good()==0)
	{
		std::cout << "Errore! Impossibile aprire file " << path << std::endl;
	}

	//initialise variables
	int n = 0;
	double sum = 0;
	double sum2 = 0;
	double mean;
	double variance;

	//do maths
	double a;
	while(infile >> a)
	{
		sum += a;
		sum2 += a*a;
		n++;
	}

	//number of entries
	values[0] = n;
	//mean
	mean = sum / n;
	values[1] = mean;
	//std error of mean
	variance = sum2 / n - mean * mean;
	values[2] = sqrt(variance / n);

	//close file
	infile.close();
	return values;
}



//returns TF1* of a chi square pdf distribution
//define gdl and draw with: chi2_PDF(gdl)->Draw();
TF1* chi2_PDF(int dof)
{
	double gammaNum = tgamma((double) (dof)/2);

	TF1* chi2 = new TF1("chi2","pow(x,([0]/2-1))*exp(-x/2)/(pow(2,[0]/2)*[1])",0,30);
	chi2->SetParameter(0, dof);  
	chi2->SetParameter(1, gammaNum);

	return chi2;
}

//returns TF1* of a student pdf distribution
//define gdl and draw with: student_PDF(gdl)->Draw();
TF1* student_PDF(int dof)
{
	double gammaNum1 = tgamma((double) (dof+1)/2);
	double gammaNum2 = tgamma((double) (dof)/2);

	TF1* student = new TF1("student","1/sqrt(pi*x) * [1]/[2] * 1/(pow((1+x*x/[0]),(([0]+1)/2)))",0,30);
	student->SetParameter(0, dof);  
	student->SetParameter(1, gammaNum1);  
	student->SetParameter(2, gammaNum2);  

	return student;
}





/*function that:
opens a file, checks it's ok
fills vector with entries in the file
close file
find min and max of data
use min max and nbin to create a TH1F
fills TH1F
*/
TH1F* makeTH1F_file(const char* filename, const char* TH1Fname, int nbins)
{
	//open file
	std::ifstream infile(filename, std::ios::in);
	if(!infile.good())
	{
		std::cout << "impossibile aprire il file" << std::endl;
		//return 1;
	}

	//fill vector with the entries in the file
	std::vector<double> data;
	double entry;
	while (infile >> entry)
	{
		data.push_back(entry);
	}

	//close file
	infile.close();

	//find min and max
	double min = *min_element(data.begin(),data.end());
	double max = *max_element(data.begin(),data.end());

	//use min, max, and set nbins to create a TH1F
	TH1F* histo = new TH1F(TH1Fname, TH1Fname, nbins, min, max);

	//fill the TH1F
	for(int i=0; i<data.size(); i++)
	{
		histo->Fill(data.at(i));
	}	

	return(histo);
}



















void scambia (double &a_ref, double &b_ref){
	double temp = a_ref;
	a_ref = b_ref;
	b_ref = temp;
	return;
}


int lungh(char*stringa){
	int i = 0;
	while(stringa[i] != '\0')
	{
		i++;
	}
	return i;
}


char *incolla(char *stringa1, char *stringa2){
	char* incollate = new char[lungh(stringa1)+lungh(stringa2)];
	for (int i=0; i<lungh(stringa1); i++)
	{
		incollate[i] = stringa1[i];
	}
	for (int j=lungh(stringa1); j<(lungh(stringa1)+lungh(stringa2)); j++)
	{
		incollate[j] = stringa2[j-lungh(stringa1)];
	}
	return incollate;
}


bool palindroma (char* parola){
	int i = 0;
	while(i<lungh(parola)/2+1)
	{
		if(parola[i] == parola[lungh(parola)-1-i])
			i++;
		else
			return false;
	}
	return true;
}


char letteraFrequente (char* stringa){
	//inizializzare array
  	double * letters = new double [26];
  	for(int i=0; i<26; i++)
  	{
   		letters[i] = 0;
  	}

	int j=0;
	while(stringa[j] != '\0')
	{
		int numtemp = (int) stringa[j];
		//lowercase (97-122)
		if(numtemp>96 && numtemp<123)
		{
		  letters[numtemp-97]++;
		}
		//uppercase (65-90)
		else if(numtemp>64 && numtemp<91)
		{
		  letters[numtemp-65]++;
		}
		j++;
	}

	int max = -1;
	char mostFreq;
	for(int i=0; i<26; i++)
	{
		if(letters[i] > max)
		{	
			max = letters[i];
			mostFreq = (char) (i+97);
		}
	}
	
	return mostFreq;
}




void sortArray (double* vettore, int lunghezza){

	bool swapped = true;
	while (swapped == true)
	{
		swapped = false;
		for(int i=0; i<(lunghezza-1); i++)
		{
			if(vettore[i] > vettore[i+1])
			{
				scambia(vettore[i], vettore[i+1]);
				swapped = true;
			}
		}
	}
	return;
}



void FizzBuzz(int i){
	char const* output = new char;
	if(i%3 == 0)
	{
		std::cout << "Fizz";
	}
	if (i%5 == 0)
	{
		std::cout << "Buzz";
	}
	else if (i%3 != 0 && i%5 != 0)
	{
		std::cout << i;
	}
	return;
}





