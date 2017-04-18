/*
c++ -o file.o ../Code/file.cpp 
*/

#include <iostream>
#include <fstream>

int main(){

	char line[256];
	std::ifstream infile;

	infile.open("../Data/pips.txt", std::ios::in);

	if(infile.good()==0)
	{
		std::cout << "Errore! Non è possibile aprire il tuo file" << std::endl;
		return (1);
	}

	while(!infile.eof())
	{
		infile.getline(line, 256);
		std::cout << "Ho letto la riga " << line << std::endl;
	}
	infile.close();


	std::ofstream outfile ("../Data/outFile.txt", std::ios::out);
	outfile << "12 24" << std::endl;
	outfile.close();

	return 0;
}