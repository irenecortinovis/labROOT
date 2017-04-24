#include "frazione.h"
#include <iostream>
#include <cmath>

using namespace std;

//constructor
frazione::frazione(const int numeratore, const int denominatore)
{
	this->numeratore = numeratore;
	this->denominatore = denominatore;
	//std::cout << "created fraction with constructor!" << std::endl;
}

//copy constructor
frazione::frazione(const frazione& other)
{
	this->numeratore = other.numeratore;
	this->denominatore = other.denominatore;
	//std::cout << "created fraction with copy constructor!" << std::endl;

}

//destructor
frazione::~frazione()
{
	//std::cout << "deleted fraction with destructor!" << std::endl;
}

//operator =
frazione& frazione::operator=(const frazione& other)
{
	this->numeratore = other.numeratore;
	this->denominatore = other.denominatore;
	std::cout << "operator =" << std::endl;
	return *this;
}

//compare
int frazione::compara(const frazione& other)
{
	int n1 = this->numeratore;
	int d1 = this->denominatore;
	int n2 = other.numeratore;
	int d2 = other.denominatore;
	
	int value = n1*d2-n2*d1;
	
	if(value > 0)
	{
		if(d1*d2>0) return 1;
		else return -1;
	}
	else if(value == 0) return 0;
	else
	{
		if(d1*d2<0) return 1;
		else return -1;
	}
}


//sum
void frazione::somma(const frazione& other)
{
	int n1 = this->numeratore;
	int d1 = this->denominatore;
	int n2 = other.numeratore;
	int d2 = other.denominatore;

	this->numeratore = n1*d2 + n2*d1;
	this->denominatore = d1*d2;
	semplifica();
}

//subtraction
void frazione::sottrai(const frazione& other)
{
	int n1 = this->numeratore;
	int d1 = this->denominatore;
	int n2 = other.numeratore;
	int d2 = other.denominatore;

	this->numeratore = n1*d2 - n2*d1;
	this->denominatore = d1*d2;
	semplifica();
}

//multiply
void frazione::moltiplica(const frazione& other)
{
	int n1 = this->numeratore;
	int d1 = this->denominatore;
	int n2 = other.numeratore;
	int d2 = other.denominatore;

	this->numeratore = n1*n2;
	this->denominatore = d1*d2;
	semplifica();
}

//divide
void frazione::dividi(const frazione& other)
{
	int n1 = this->numeratore;
	int d1 = this->denominatore;
	int n2 = other.numeratore;
	int d2 = other.denominatore;

	this->numeratore = n1*d2;
	this->denominatore = d1*n2;
	semplifica();
}

//simplify
void frazione::semplifica()
{
	double minimo;
	if(numeratore > denominatore)
		minimo = denominatore;
	else minimo = numeratore;

	double mcd =1;
	for (int i=2; i<=minimo; i++)
	{
		if(numeratore%i == 0 && denominatore%i == 0)
			mcd = i;
	}

	this->numeratore /= mcd;
	this->denominatore /= mcd;

}

//print
void frazione::stampa() const
{
	if(this->numeratore * this->denominatore > 0)
		std::cout << abs(numeratore) << "/" << abs(denominatore) << std::endl;
	else if(this->numeratore * this->denominatore < 0)
		std::cout << "-" << abs(numeratore) << "/" << abs(denominatore) << std::endl;
	else if(this->numeratore * this->denominatore == 0)
	{
		if(this->denominatore == 0)
			std::cout << "nan, 0 at denominator" << std::endl;
		else
			std::cout << "0" << std::endl;
	}
}


