#ifndef vettore_h
#define vettore_h

class vettore
{

public:
	//ctor
	vettore();
	//ctor with size
	vettore(const int &size);
	//dtor
	~vettore();

	//metodi
	int getSize();
	int getEntry(const int	&nEntry);
	void print();
	const vettore& push(const int& number);
	void pop();

private:
	int size_p;
	int* vec;

};

#endif
