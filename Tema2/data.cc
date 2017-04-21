#include <iostream>
#include <string>
#include "data.h"

using namespace std;

//constructor
data::data(const int day, const int month, const int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

//copy constructor
data::data(const data& other)
{
	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
}

//operator =
data& data::operator=(const data& other)
{
	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
	return *this;
}

//operator ==
bool data::operator==(const data& other) const
{
	bool checkDay = (this->day == other.day);
	bool checkMonth = (this->month == other.month);
	bool checkYear = (this->year == other.year);
	if(checkDay && checkMonth && checkYear)
		return true;
	else
		return false;
}


bool data::operator<(const data& other) const
{
	if //n giorni moltiplica
}

//sistemare
void data::stampa() const
{
	std::cout << this->day << "/" << this->month << "/" << this->year << std::endl;
}

void data::imposta(int day, int month, int year){}

bool data::valida() const{}
int data::diff_giorni(const data other) const{}
string data::giorno_settimana() const{}




