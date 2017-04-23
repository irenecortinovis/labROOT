# ifndef lib_h
# define lib_h

#include <cmath>
#include <TMath.h>

int fsommatoria (int vett[], int size)
	{
	if (size <= 0) return -1;
	
	int qui = 0;
	for (int i = 0; i < size; i++)
		{
		qui += vett[i];
		}
	return qui;
	}


double fmedia (int vett[], int size)
	{
	double media = 0;
	for (int i = 0; i < size; i++)
		{
		media += i*vett[i];
		}
	media /= fsommatoria (vett, size);
	return media;
	}


double fsigma (int vett[], int size)
	{
	double mediasc = 0;
	for (int i = 0; i < size; i++)
		{
		mediasc += vett[i]*pow(i-fmedia (vett, size), 2);
		}
	mediasc /= (fsommatoria (vett, size)-1);
	double sigma = sqrt(mediasc);
	return sigma;
	}


double ffattoriale (int n)
	{
	if (n == 0)
		return 1;
	else
		return n * ffattoriale(n-1);
	}


double fformula (double mu, int n, int freq)
	{
	double val = exp(-mu) * pow (mu, n);
	val /= ffattoriale(n);
	val = pow (val, freq);
	return val;
	}


double flikelihood (double mu, int vett[], int size)
	{
	double l = 1;
	for (int n = 0; n < size; n++)
		{
		l *= fformula (mu, n, vett[n]);
		}
	return log(l);
	}	


double tris (double x0, double x1, double prec, int vett[], int size)
	{
	if (fabs(x1 -x0) < prec) return 0.5 * (x0 + x1);

	double x2 = x0 + ((x1 - x0)/3);
	double x3 = x1 - ((x1 - x0)/3);

	if (flikelihood (x2, vett, size) < flikelihood (x3, vett, size)) return tris (x1, x2, prec, vett, size);
	else return tris (x0, x3, prec, vett, size);
	}


double ferrori (double mu, double mL, int vett[], int size)
	{
	double val = flikelihood (mu, vett, size);
	val -= flikelihood (mL, vett, size);
	val += 0.5;
	return val;
	}


double fsmazza (double mL, double min, double max, double prec, int vett[], int size)
	{
	double medio = 0.5 * (min + max);

	if ((max - min) < prec) return medio;
	if (ferrori(medio, mL, vett, size)*ferrori(min, mL, vett, size) < 0)
		return fsmazza (mL, min, medio, prec, vett, size);		
	else return fsmazza (mL, medio, max, prec, vett, size);
	} 

double frettoli (double xmin, double xmax, int vett[], int size)
	{
	double step = (xmax - xmin)/1000.;
	double x = xmin;
	double integ = 0.;
	while (x < xmax)
		{
		double h = exp(flikelihood (0.5 * (x+x+step), vett, size));
		integ += h*step;
		x += step; 
		}
	return integ;
	}

double fpois (double * x, double * par)
	{
	return par[0]*TMath::Poisson (x[0], par[1]);
	}

# endif
