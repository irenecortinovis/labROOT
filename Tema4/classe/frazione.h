#ifndef FRAZIONE_H
#define FRAZIONE_H

using namespace std;

class frazione {
	public:
		frazione(const int numeratore, const int denominatore);
		frazione(const frazione& other);
		~frazione();

		frazione& operator=(const frazione& other);

		int compara(const frazione& other);
		void somma(const frazione& other);
		void sottrai(const frazione& other);
		void moltiplica(const frazione& other);
		void dividi(const frazione& other);

		void semplifica();
		void stampa() const;

	private:
		int numeratore;
		int denominatore;
};

#endif
