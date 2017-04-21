#include <iostream>
#include <string>
#include <cmath>
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

//operator <
bool data::operator<(const data& other) const
{
	if(this->year < other.year)
		return true;
	else if(this->year > other.year)
		return false;
	else
	{
		if(this->month < other.month)
			return true;
		else if(this->month > other.month)
			return false;
		else
		{
			if(this->day < other.day)
				return true;
			else 
				return false;
		}
	}
}

//sistemare
void data::stampa() const
{
	std::cout << this->day << "/" << this->month << "/" << this->year << std::endl;
}

//imposta giorno mese e data dati in input
void data::imposta(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}



//validate date
bool data::valida() const
{
	bool valida = true;

	//day>0 and 0<month<12
	if(this->day <= 0 || this->month < 0 || this->month > 12)
		valida = false;

	//check n days
	//days of february (29, but 28 if bisestile)
	int feb = 28;
	if((this->year)%400 == 0 || ((this->year)%4 == 0 && (this->year)%100 != 0))
		feb = 29;
	//array of days of the month
	int daysMonth[12] = {31, feb, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(this->day > daysMonth[(this->month)-1])
		valida = false;

	return valida;
}

int data::n_giorni() const
{
	int day = this->day;
	int month = this->month;
	int year = this->year;

	// ---- YEAR -------
	// n of days in period of n years
	int days1 = 365;
	int days4 = 4*days1 + 1;
	int days100 = 25*days4 - 1;
	int days400 = 4*days100 + 1;
	//compute n of days from year 0
	int ndaysYear = (year-1)/400 * days400 + ((year-1)%400)/100 * days100 + ((year-1)%100)/4 * days4 + ((year-1)%4) * days1;

	// ------- MONTH ------
	//days of february (29, but 28 if bisestile)
	int feb = 28;
	if((this->year)%400 == 0 || ((this->year)%4 == 0 && (this->year)%100 != 0))
		feb = 29;
	//array of days of the month
	int daysMonth[13] = {0, 31, feb, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int ndaysMonth = 0;
	for(int i=0; i<month; i++)
		ndaysMonth += daysMonth[i];

	// -------- DAY ------
	int ndays = day;

	return ndaysYear + ndaysMonth + ndays;
}



int data::diff_giorni(const data other) const
{
	return this->n_giorni() - other.n_giorni();
}



string data::giorno_settimana() const
{
	//array of string days
	string week[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

	//today is friday
	data today(21, 4, 2017);
	int itoday = 4;

	int diff = this->diff_giorni(today);
	string weekday;
	if(diff>=0)
	{
		weekday = week[(((diff%7 + itoday))%7)];
	}
	else
	{
		int index = ((-((-diff)%7) + itoday))%7;
		if(index>0)
			weekday = week[(((-((-diff)%7) + itoday))%7)];
		else
			weekday = week[7+(((-((-diff)%7) + itoday))%7)];
	}

	return weekday;
}




