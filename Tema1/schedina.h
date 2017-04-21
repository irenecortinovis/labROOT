#ifndef schedina_h
#define schedina_h

#include <string>

using namespace std;

#define UNO 1
#define DUE 2
#define ICS 3

class schedina {

	public:
		schedina(const string filename);
		schedina(const schedina &original);
		~schedina();

		schedina& operator=(const schedina& original);

		void Print() const;
		void DisputaPartite();
		int RisultatoScommessa() const;
		

	private:
		string *squadra_1;
		string *squadra_2;
		int *pronostico;
		int *risultati;
};

#endif
