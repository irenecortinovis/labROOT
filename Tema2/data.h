#ifndef data_h
#define data_h
#include <string>

using namespace std;

class data {

	public:
		data(const int day, const int month, const int year);
		data(const data& other);
		data& operator=(const data& other);
		bool operator==(const data& other) const;
		bool operator<(const data& other) const;

		// metodi gia' implementati nel file H
		bool operator!=(const data& other) const { return !this->operator==(other); }
		bool operator>(const data& other) const { return other.operator<(*this); }
		bool operator<=(const data& other) const { return !this->operator>(other); }
		bool operator>=(const data& other) const { return !this->operator<(other); }

		void stampa() const;
		void imposta(int day, int month, int year);

		bool valida() const;
		int diff_giorni(const data other) const;
		string giorno_settimana() const;

	private:
		int year, month, day;

};

#endif
