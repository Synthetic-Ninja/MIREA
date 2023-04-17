#include "atype.h"
#include <stdlib.h> 

using namespace std;

int main()
{	
	arr <int> My_Int(5);

	for(int i = 0; i < 5; i++)
	{
		int r = ((double)rand() / RAND_MAX) * (100 - 1) + 1;
		My_Int[i] = r;
	}

	cout << endl << "Неотсортированный массив" << endl;
	My_Int.Out();
	My_Int.Sort();
	cout << endl << "Отсортированный массив" << endl;
	My_Int.Out();

	arr <string> My_String(5);
	My_String[0] = "Абрамов";
	My_String[1] = "Столыпин";
	My_String[2] = "Сталин";
	My_String[3] = "Гордеев";
	My_String[4] = "Анимов";
	
	cout << endl << "Неотсортированный массив" << endl;
	My_String.Out();
	My_String.Sort(My_String[0]);
	cout << endl << "Отсортированный массив" << endl;
	My_String.Out();
}
