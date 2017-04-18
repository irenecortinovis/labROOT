#ifndef labII_h
#define labII_h

#include "TF1.h"
#include "TH1F.h"
#include <vector>
#include <algorithm>



double rand_range(double min, double max);
//problem with min and max, because of int rounding
int rand_range(int min, int max);

double f_gaus(double x);

double rand_TryAndCatch(double f(double), double xMin, double xMax,
				double yMin, double yMax);

double bisectionRecursive(double f(double), double xMin,
						  double xMax, double precision);

double integral_montecarlo(double f(double), double xMin, double xMax,
						   double yMin, double yMax, int max_num);

double integral_riemann(double f(double), double xMin,
						double xMax, double nBins);

//inverse function random generator

/*
opens file (checking)
calculates n of entries, mean, error of mean
saves them in array
closes file and returns array
*/
double* data_analysis(const char* path);


//returns TF1* of a chi square pdf distribution
//define gdl and draw with: chi2_PDF(gdl)->Draw();
TF1* chi2_PDF(int dof);

//returns TF1* of a student pdf distribution
//define gdl and draw with: student_PDF(gdl)->Draw();
TF1* student_PDF(int dof);


/*function that:
opens a file, checks it's ok
fills vector with entries in the file
close file
find min and max of data
use min max and nbin to create a TH1F
fills TH1F */
TH1F* makeTH1F_file(const char* filename, const char* TH1Fname, int nbins);


void scambia (double &a_ref, double &b_ref);
int lungh(char * stringa);
char *incolla(char *stringa1, char *stringa2);
bool palindroma (char* parola);
char letteraFrequente (char* stringa);
void sortArray (double* vettore, int lunghezza);
void FizzBuzz(int i);




#endif