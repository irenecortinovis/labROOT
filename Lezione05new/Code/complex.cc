#include "complex.h"
#include <iostream>
#include <cmath>




//default ctor
complex::complex(){
	re_p = 0;
	im_p = 0;
}

//ctor re im
complex::complex(const double& Re, const double& Im){
	re_p = Re;
	im_p = Im;
}

//ctor rho theta
complex::complex(const double& Rho, const double& Theta, bool flag){
	re_p = Rho * cos(Theta);
	im_p = Rho * sin(Theta);
}


//operator =()
complex& complex::operator=(const complex& original){
	re_p = original.re_p;
	im_p = original.im_p;
	return *this;
}


//operator +()
complex& complex::operator+(const complex& addendum){
	re_p += addendum.re_p;
	im_p += addendum.im_p;
	return *this;
}

//methods

//real
double complex::Re(){
	return re_p;
}

//imaginary
double complex::Im(){
	return im_p;
}

//modulus
double complex::Mod(){
	return sqrt(re_p*re_p + im_p*im_p);
}

//argument in radians
double complex::Theta(){
	return atan(im_p/re_p);
}

void complex::Print() const{
	if (im_p>=0) std::cout << re_p << "+i" << im_p << std::endl;
  	else std::cout << re_p << "-i" << im_p << std::endl;
}
