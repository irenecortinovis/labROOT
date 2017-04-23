/*
compile with:

c++ data.cc dataclass.cpp -o dataclass.o

*/


#include <iostream>
#include <string>
#include "data.h"

int main(){

	//constructor
	int day = 3;
	int month = 10;
	int year = 1996;
	data test(day, month, year);
	std::cout << "\nTesting default constructor: " << std::endl;
	test.stampa();

	//copy constructor
	data testCopy(test);
	std::cout << "\nTesting copy constructor: " << std::endl;
	testCopy.stampa();

	//operator =
	data testAssign = test;
	std::cout << "\nTesting = operator: " << std::endl;
	testAssign.stampa();

	//operator ==
	data testSame1(4, 10, 1996);
	data testSame2(3, 11, 1996);
	data testSame3(3, 10, 1997);

	std::cout << "\nTesting == operator: " << std::endl;
	if(test == testSame1) std::cout << "error\t";
	else std::cout << "ok\t";
	if(test == testSame2) std::cout << "error\t";
	else std::cout << "ok\t";
	if(test == testSame3) std::cout << "error\t";
	else std::cout << "ok\t";
	if(test == testCopy) std::cout << "ok" << std::endl;
	else std::cout << "error" << std::endl;

	//operator <
	std::cout << "\nTesting < operator: " << std::endl;
	if(test < testSame1) std::cout << "ok\t";
	else std::cout << "error\t";
	if(test < testSame2) std::cout << "ok\t";
	else std::cout << "error\t";
	if(test < testSame3) std::cout << "ok\t";
	else std::cout << "error\t";
	if(test < testCopy) std::cout << "error" << std::endl;
	else std::cout << "ok" << std::endl;

	//imposta
	data testImposta = test;
	std::cout << "\nTesting imposta: " << std::endl;
	testImposta.stampa();

	testImposta.imposta(4, 11, 1997);
	testImposta.stampa();

	//valida
	data testValida1(0, 13, 1996);
	if(testValida1.valida() == false) std::cout << "ok\t";
	else std::cout << "error\t";

	data testValida2(29, 2, 2000);
	if(testValida2.valida() == true) std::cout << "ok\t";
	else std::cout << "error\t";

	data testValida3(29, 2, 2100);
	if(testValida3.valida() == false) std::cout << "ok\t";
	else std::cout << "error\t";

	data testValida4(29, 2, 2004);
	if(testValida4.valida() == true) std::cout << "ok\t";
	else std::cout << "error\t";

	data testValida5(29, 2, 2003);
	if(testValida5.valida() == false) std::cout << "ok" << std::endl;
	else std::cout << "error" << std::endl;

	//test n_days
	std::cout << "\nTesting n_giorni: " << std::endl;
	std::cout << test.n_giorni() << std::endl;

	data testNdays1(2, 1, 0);
	std::cout << testNdays1.n_giorni() << std::endl;

	data testNdays2(1, 1, -1);
	std::cout << testNdays2.n_giorni() << std::endl;

	data testNdays3(1, 1, -2);
	std::cout << testNdays3.n_giorni() << std::endl;


	//test diff_giorni
	std::cout << "\nTesting diff_giorni" << std::endl;

	data today(21, 4, 2017);
	std::cout << today.diff_giorni(test) << std::endl;

	data testdiff1(1, 1, 0);
	std::cout << testdiff1.n_giorni() << std::endl;
	data testdiff2(31, 12, -1);
	std::cout << testdiff2.n_giorni() << std::endl;
	std::cout << testdiff1.diff_giorni(testdiff2) << std::endl;

	data testdiff3(28, 2, 2004);
	data testdiff4(1, 3, 2004);
	if(testdiff4.diff_giorni(testdiff3) == 2)
		std::cout << "ok\t";
	else std::cout << "error\t";

	data testdiff5(28, 2, 2100);
	data testdiff6(1, 3, 2100);
	if(testdiff6.diff_giorni(testdiff5) == 1)
		std::cout << "ok\t";
	else std::cout << "error\t";

	data testdiff7(28, 2, 2400);
	data testdiff8(1, 3, 2400);
	if(testdiff8.diff_giorni(testdiff7) == 2)
		std::cout << "ok\t";
	else std::cout << "error\t";
		
	data testdiff9(28, 2, 2401);
	data testdiff10(1, 3, 2401);
	if(testdiff10.diff_giorni(testdiff9) == 1)
		std::cout << "ok\t";
	else std::cout << "error\t";

	data testdiffa(31, 12, 1987);
	data testdiffb(1, 1, 1988);
	if(testdiffb.diff_giorni(testdiffa) == 1)
	std::cout << "ok" << std::endl;
	else std::cout << "error" << std::endl;

	//test giorno_settimana
	std::cout << "\nTesting giorno_settimana" << std::endl;

	std::cout << "today (friday): " << today.giorno_settimana() << std::endl;

	data tomorrow(22, 4, 2017);
	std::cout << "tomorrow (saturday): " << tomorrow.giorno_settimana() << std::endl;

	data yesterday(20, 4, 2017);
	std::cout << "yesterday (thursday): " << yesterday.giorno_settimana() << std::endl;

	data megatest(1, 1, 2017);
	std::cout << "date (sunday): " << megatest.giorno_settimana() << std::endl;

	data megatest1(29, 2, 1888);
	if(megatest1.valida())
		std::cout << "date (wednesday): " << megatest1.giorno_settimana() << std::endl;
	









	return 0;
}