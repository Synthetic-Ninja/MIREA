#include "truncatedcone.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	TruncatedСone cone1;
	TruncatedСone cone2;
	Cone parentcone;

	cout << "Введите Радиус нижнего основания, Высоту полного конуса, Радиус верхнего основания, высоту усеченного конуса, x, y, z через запятую\n: ";
	cin >> cone1;
	cout << cone1;

	cout << "\n" << endl;
	cout << "Введите Радиус нижнего основания, Высоту полного конуса, Радиус верхнего основания, высоту усеченного конуса, x, y, z через запятую\n: ";
	cin >> cone2;
	cout << cone2;

	cout << "\n" << endl;
	cout << "cone1 > cone2: " << (cone1 > cone2? "Yes" : "No") << endl;
	cout << "cone1 < cone2: " << (cone1 < cone2? "Yes" : "No") << endl;
	cout << "cone1 == cone2: " << (cone1 == cone2? "Yes" : "No") << endl;
	cout << "cone1 <= cone2: " << (cone1 <= cone2? "Yes" : "No") << endl;
	cout << "cone1 >= cone2: " << (cone1 >= cone2? "Yes" : "No") << endl;

	
	

	Cone basedcone; // Базовый конус

	cout << "Дочерний усеченный конус производный от базового конуса\n\n";
	TruncatedСone childcone(basedcone); // Производный от базового без указания h2, r2
	cout << childcone;

	TruncatedСone childcone2(basedcone, 1, 2); // Производный от базового с указанием h2, r2
	cout << childcone2;


	return 0;
}